# CSS432_22W_MogulSolutions

Needs:
  - Game menu
    + menu locks player into game
  - Game Session
    + provides mutual exclusion of game state writes between 2 sessions
    + after each game, record updated and recordDB saved to disk
  - games list menu
  - game logic

Wants:
  - leaderboard menu
  - in-game chat
  - player logout
  - track players logged in (prevent multiple logins of same profile at one time)
  - on-exit server saves recordDB to disk

Hopes:
  - ensure 100% no deadlocks ever
  - guest sign-in
  - provide admin commands on the server side (i.e. flush records, view sessions, kill sessions, view general debug info, active players, kick players)

Dreams:
  - end-to-end encryption
  - lexer generates token after only a single pass of the command (flex?)
  - create a windows version of client.cpp
  - create an html website for clients
  - run the server on the cloud
  - implement admin permissions for certain accounts

https://lucid.app/lucidchart/5530d58d-dd9d-4ec0-8f6c-e628224479e6/edit?invitationId=inv_69021b0a-8ebb-41fc-8444-9489197684e4

![image](https://user-images.githubusercontent.com/72415858/156201626-a4031eb9-d229-43bd-a5e0-615cd195cea7.png)

