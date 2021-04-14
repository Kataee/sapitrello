# sapitrello

sapitrello(1) is a command-line based kanban project management tool, similar to
Trello. It is written in the C programming language, as a group project for the
Information and Computer Science class from Sapientia Hungarian University of
Transylvania.

## Usage

sapitrello uses the [STQL format][stql-docs] to run operations on the database.
You may either open the application directly and run the statements manually, or
you can read a set of statements from a file:

```
sapitrello -i input.stql
```

No data will be saved to the disk until you run the `save` command. The app will
save your database to a file called `data.stdb`. This file is useful in terms of
portability and the open spec also makes it possible for developers to create
their own wrappers around the format (in whatever programming language they
prefer).

You can read more about the STDB format [here][stdb-docs].

## Prerequisites

- C compiler (GCC is recommended)
- cmake (3.0.0 and above)
- git for cloning files

## Getting Started

**Clone the repository:**

```
git clone git@github.com:Kataee/sapitrello.git
cd sapitrello
```

**Generate build files:**

```
mkdir build && cd build
cmake .. -B .
```

**Build the app:**

```
cmake --build .
```

## Developers

- Ottó Tövisi (@Kataee)
- Napsugár Veress (@napsugarinf)
- József Sallai (@jozsefsallai)

**Supervisor:** Boróka Olteán-Péter (@borokaoltean)

## Disclaimer

This project is not affilated with or endorsed by Trello/Atlassian. It does not
use the Trello API or any other external APIs.

## License

The program is licensed under MIT. Check `LICENSE` for more detais.

[stdb-docs]: https://github.com/Kataee/sapitrello/blob/main/docs/STDB_FORMAT.md
[stql-docs]: https://github.com/Kataee/sapitrello/blob/main/docs/STQL_FORMAT.md
