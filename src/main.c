/* navi.c  - maksim yarorvoy 22.03.25 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define MAX_FILE_SIZE 1024 * 1024
#define WIDTH 80
#define HEIGHT 24

void set_terminal_mode(struct termios *old_tio) {
    struct termios new_tio;
    tcgetattr(STDIN_FILENO, old_tio);
    new_tio = *old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    new_tio.c_cc[VMIN] = 1;
    new_tio.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_terminal_mode(const struct termios *old_tio) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_tio);
}

char get_key() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
}

void clear_screen() {
    printf("\033[H\033[J");
    fflush(stdout);
}

void print_text(const char *text, int cursor_pos, int width, int height) {
    int row = 1, col = 1;
    int len = strlen(text);
    int start = cursor_pos / (width * height) * width * height;
    int end = start + width * height;

    for (int i = start; i < end && i < len; i++) {
        if (col > width) {
            col = 1;
            row++;
        }
        if (text[i] == '\n') {
            col = 1;
            row++;
        } else {
            putchar(text[i]);
            col++;
        }
    }

    move_cursor(row, col);
    fflush(stdout);
}

void insert_char(char *text, int *cursor_pos, char ch) {
    memmove(&text[*cursor_pos + 1], &text[*cursor_pos], strlen(&text[*cursor_pos]) + 1);
    text[*cursor_pos] = ch;
    (*cursor_pos)++;
}

void delete_char(char *text, int *cursor_pos) {
    if (*cursor_pos > 0) {
        memmove(&text[*cursor_pos - 1], &text[*cursor_pos], strlen(&text[*cursor_pos]) + 1);
        (*cursor_pos)--;
    }
}

void print_help() {
    printf("Simple text editor\n\n");
    printf("Usage: editor <filename>\n");
    printf("Commands:\n");
		printf("NaGNU/NaVi - simple text editor\n");
    printf("  Ctrl+X   - Save and exit\n");
    printf("  Ctrl+C   - Exit without saving\n");
    printf("  Arrow keys - Move cursor\n");
    printf("  Backspace - Delete character\n");
    printf("  Enter - Insert new line\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char filename[256];
    strncpy(filename, argv[1], sizeof(filename) - 1);

    char text[MAX_FILE_SIZE] = {0};
    int cursor_pos = 0;

    FILE *file = fopen(filename, "r+");
    if (!file) {
        file = fopen(filename, "w+");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
    }

    size_t file_size = fread(text, 1, MAX_FILE_SIZE - 1, file);
    fclose(file);

    struct termios old_tio;
    set_terminal_mode(&old_tio);

    clear_screen();
    printf("NaGNU/NaVi. Press Ctrl+X to exit.\n");

    while (1) {
        clear_screen();
        print_text(text, cursor_pos, WIDTH, HEIGHT);
        move_cursor(1, 1);

        char key = get_key();

        if (key == 3) {
            break;
        } else if (key == 24) {
            file = fopen(filename, "w");
            fwrite(text, 1, strlen(text), file);
            fclose(file);
            break;
        } else if (key == 10) {
            insert_char(text, &cursor_pos, '\n');
        } else if (key == 127) {
            delete_char(text, &cursor_pos);
        } else if (key == 27) {
            get_key();
            char direction = get_key();
            if (direction == 'C' && cursor_pos < strlen(text)) cursor_pos++;
            if (direction == 'D' && cursor_pos > 0) cursor_pos--;
        } else {
            insert_char(text, &cursor_pos, key);
        }
    }

    restore_terminal_mode(&old_tio);
    return 0;
}
