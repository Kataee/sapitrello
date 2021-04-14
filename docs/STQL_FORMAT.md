# STQL (Sapitrello Query Language) Format Specification

STQL is our in-house query language for working with sapitrello. It is heavily
inspired by SQL and is used both in the command line interface and external
files.

STQL statements are case insensitive, however the variable arguments passed to
certain statements are case-sensitive (e.g.: the title of a card). Certain
arguments can consist of multiple words separated by a space character. If an
argument has multiple words, it must always be enclosed between double quotes.
Otherwise the double quotes are not necessary.

Multiple STQL statements can be run in the same line as long as they are
separated by a semicolon `;` character. The last statement does not require a
trailing semicolon. A line of statements cannot exceed 4095 characters.

STQL statements will run certain commands.

## `CREATE`

Used to create an entry in a given model (user, board or card).

### Create user

Creates a new user with a given name and email.

```sql
CREATE USER "Jozsef Sallai" WITH EMAIL joe@somus.app;
```

### Create board

Creates a new board with a given name.

```sql
CREATE BOARD sapitrello;
```

### Create card

Creates a new card with a given title.

```sql
CREATE CARD "Finish STQL parser";
```

You can also create a card with a description by passing `WITH DESCRIPTION` to
the statement. The application will then ask you to provide the description:

```sql
CREATE CARD sapitrello WITH DESCRIPTION;
```

## `SHOW`

Used to list entries in a model collection.

### `SHOW USERS`

Will print out the list of all users added to the sapitrello database.

```sql
SHOW USERS;
```

### `SHOW BOARDS`

Will print out the list of all boards created within the application.

```sql
SHOW BOARDS;
```

### `SHOW CARDS`

**Only available when an active board is selected.**

Will print out the list of all cards created within a board.

```
SHOW CARDS;
```

You can set a filter for a card's title (case-sensitive):

```sql
SHOW CARDS WHERE TITLE IS "Finish STQL parser";
```

You can also set a filter for a card's status:

```sql
SHOW CARDS WHERE STATUS IS TODO;
SHOW CARDS WHERE STATUS IS DOING;
SHOW CARDS WHERE STATUS IS DONE;
```

### `SHOW MEMBERS`

**Only available when an active board is selected.**

Will print out the list of members added to the board.

```sql
SHOW MEMBERS;
```

## `USE`

### `USE BOARD`

Will change the active board to the one with the given ID.

```sql
USE BOARD 0;
```

## `ADD`

### `ADD USER`

Adds user with a given ID to a board with a given ID.

```sql
ADD USER 0 TO BOARD 0;
```

## `ASSIGN`

### `ASSIGN USER`

**Only available when an active board is selected.**

Sets user with a given ID as the top assignee of a card with a given ID. Only
users that were added to the board can be assigned.

```sql
ASSIGN USER 0 TO CARD 0;
```

## `DESCRIBE`

### `DESCRIBE CARD`

Prints out information as well as the list of assignees for a card with a given
ID.

```sql
DESCRIBE CARD 0;
```

## `SELECT`

**Only available when an active board is selected.**

Will extract a given field from a card with a given ID.

```sql
SELECT TITLE FROM CARD 0;
SELECT DESCRIPTION FROM CARD 0;
SELECT STATUS FROM CARD 0;
SELECT ASSIGNEES FROM CARD 0;
```

## `UPDATE`

### `UPDATE CARD`

**Only available when an active board is selected.**

Updates a field in a card with a given ID.

```sql
UPDATE CARD 0 SET TITLE "Fix STQL parser";
UPDATE CARD 0 SET DESCRIPTION;
UPDATE CARD 0 SET STATUS TODO;
UPDATE CARD 0 SET STATUS DOING;
UPDATE CARD 0 SET STATUS DONE;
```

Note: `SET DESCRIPTION` will prompt the user for a new description. Currently
there is no way to cancel this operation.

## `DELETE`

Deletes an item from a model collection.

### `DELETE CARD`

**Only available when an active board is selected.**

Deletes a card with a given ID.

```sql
DELETE CARD 0;
```

### `DELETE BOARD`

Deletes a board with a given ID.

```sql
DELETE BOARD 0;
```

### `DELETE USER`

Deletes a user with a given ID. Will also remove the user from all boards they
were added to and all cards they were assigned to.

```sql
DELETE USER 0;
```

### `DELETE MEMBER`

**Only available when an active board is selected.**

Deletes a member with a given ID from the active board.

```sql
DELETE MEMBER 0;
```

## `SAVE`

Save all in-memory changes that have been made to the database to the
[data.stdb](stdb-docs) database file.

```sql
save
```

## `EXIT`

Closes the application.

```sql
exit
```

[stdb-docs]: https://github.com/Kataee/sapitrello/blob/main/docs/STDB_FORMAT.md
