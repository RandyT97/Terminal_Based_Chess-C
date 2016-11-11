# Basic Command Prompt Based Chess Program (C)
Print based chess game in C
I am going to code a chess program for my final project and will be working on this program on my own.
I want to make a chess program that has the following features:

#Fundamental Features:
  Proper setup of board:
  The starting position of a standard chess game should be like the following: (Image from:https://en.wikipedia.org/wiki/Chess)


  Proper Capture of Pieces: 
  Upon moving a piece to an occupied location, the piece at the location should be “captured” and therefore removed from the board.
  
  Proper Movement of Pieces:
  
  There are six different movement patterns of pieces in chess
  
    Knight: T-shaped 
    
      NOTE: Aside from the knight, other pieces cannot simply go “through” other pieces. 
      Only the knight has the ability to “jump” over occupied squares.
    
    Rook: Can limitlessly move in the vertical and horizontal direction.
    
    Pawn: One piece forward, can only capture if piece is in a diagonal one coordinate away from the pawn.
    
    Queen: Can limitlessly move throughout the board diagonally, horizontally and vertically.
    
    King: Can move one unit in any direction.
    
    Bishop: Can move diagonally an unlimited distance.
    
  Exceptions:
    
    The pawn can move forward two units from the starting position.
    In castling, if the path between a sides’ rook and king is clear, the player has an option of moving the rook to 
    the unit nearest the king and have the king move to the unit next to the rook in the direction of the rook's
    initial position.
    
    In en pessant, if the pawn of user A has not moved, and pawn of user b threatens the unit in front of user A’s
    pawn, and user A decides to move the pawn two units forward in an attempt to avoid capture, user B can still 
    capture and moves diagonally one unit as if user A moved the pawn only one unit forward.
    
  Piece Promotion
  
    When a user has moved a pawn of his/hers to the first row of the opposing side of the board, has the option 
    to promote the pawn and replace it with any piece of choice other than king.
    
  Making sure the two players have distinguishable pieces
  
    Differentiate the two player’s pieces, as simply labeling each piece according to their name will confuse 
    ownership of pieces.
    
    
  Endgame
  
    Game ends upon check mate
    
#Optional Features:
   Game notations (text record of game)
   
     In chess there are different forms of notation in which the game can be recorded.
     
  Timer
  
    Prompt user for time options.
    
  Chess variants:
  
    Chess960: Randomly generate the starting location of each person’s pieces in their first two rows
    
    Horde: One user has 36 pawns, while the other has a normal chess setup.
    
 Start Menu and a way for users to return to the start menu while in a game.
 
  User profiles
  
    To store statistics such as games played/won, head to head record, etc.
    
  A low skill chess bot.
