# NaVi

Just text, control, and simplicity. The NaGNU way.

## Overview

NaVi is a theoretical concept of a lightweight, fast, and minimalistic console text editor written in C. Designed as part of the NaGNU project, NaVi aims to be the best editor for your NaGNU/Linux system.

## Philosophy

Minimalism — No unnecessary features, only what you really need.

Speed — Instant startup and responsive behavior.

Simplicity — Easy to learn, intuitive, and predictable.

Freedom — Fully open-source, built for the NaGNU ecosystem.

Planned Architecture

Clean C codebase with POSIX compatibility.

Simple loop structure: input → processing → rendering.

Terminal-based rendering without external libraries.

Buffer management with undo history.

## Modes

Normal Mode — Navigate and execute commands.

Insert Mode — Edit and type text.

Command Mode — Triggered by :, for saving, quitting, and other actions.

Keybindings (Conceptual)

Key

Action

h / j / k / l

Move left / down / up / right

i

Enter insert mode

Esc

Exit insert mode / return to normal mode

:w

Save file

:q

Quit

:wq

Save and quit

Core Features (Planned)

Open file by argument or command.

Save to file.

Basic search functionality.

Undo last action.

Optional simple syntax highlighting.

Configuration (Future Roadmap)

Config file: ~/.navi.conf

Custom keybindings.

Color scheme customization.

## Project Status

NaVi is currently in theoretical design stage. Implementation will follow the principles outlined above.

## License

NaVi will be released under a permissive open-source license (planned: MIT).

## Part of the NaGNU Project

NaVi is designed to seamlessly fit into the NaGNU/Linux philosophy: simplicity, transparency, and full user control.

## Contact

Have ideas or want to contribute to the design phase? Stay tuned for repository announcements or join the NaGNU community discussions.

NaVi — part of the NaGNU project and the best editor for your NaGNU/Linux system.

