# STDB (Sapitrello Database) Format Specification

sapitrello uses its own file format to store users, boards, and cards. It's
called STDB and is always located right next to the app's executable under the
name "data.stdb". If the file does not exist, the app will start with an empty
database. Currently, the location and the name of the file cannot be changed.

The specification of the format is as follows:

- **1x 1 byte, unsigned char**: magic number - always 137 (0x89)
- **4x 1 byte, char**: magic header - ASCII for "SAPI"
- **1x 4 bytes, int**: number of users
- **1x 4 bytes, int**: number of boards
- **1x 4 bytes, int**: number of cards
- list of users
- list of boards
- list of employees

To save a file, run `save` in the sapitrello command line:

```
sapitrello> save;
```
