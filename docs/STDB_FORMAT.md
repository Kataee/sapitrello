# STDB (Sapitrello Database) Format Specification

sapitrello uses its own file format to store users, boards, and cards. It's
called STDB and is always located right next to the app's executable under the
name "data.stdb". If the file does not exist, the app will start with an empty
database. Currently, the location and the name of the file cannot be changed.

The specification of the format is as follows:

- **1x 1 byte, uchar**: magic number - always 137 (0x89)
- **4x 1 byte, char**: magic header - ASCII for "SAPI"
- **1x 4 bytes, uint**: number of users
- **1x 4 bytes, uint**: number of boards
- **1x 4 bytes, uint**: number of cards
- for each user:
  - **1x 4 bytes, uint**: ID of the user
  - **1x 4 bytes, uint**: length of the user's name
  - **len x 1 byte, char**: name of the user
  - **1x 4 bytes, uint**: length of the user's email
  - **len x 1 byte, char**: email of the user
- for each card
  - **1x 4 bytes, uint**: ID of the card
  - **1x 4 bytes, uint**: length of the card's title
  - **len x 1 byte, char**: the title of the card
  - **1x 4 bytes, uint**: length of the card's description
  - **len x 1 byte, char**: the description of the card
  - **1x 4 bytes, uint**: number of users assigned to the card
  - **nr x 4 bytes, uint**: IDs of the users assigned to the card
- for each board
  - **1x 4 bytes, uint**: ID of the board
  - **1x 4 bytes, uint**: length of the board's name
  - **len x 1 byte, char**: the name of the board
  - **1x 4 bytes, uint**: number of members in the board
  - **1x 4 bytes, uint**: number of cards in the board
  - **nr_memb x 4 bytes, uint**: IDs of the members of the board
  - **nr_card x 4 bytes, uint**: IDs of the cards added to the board

To save a file, run `save` in the sapitrello command line:

```
sapitrello> save;
```
