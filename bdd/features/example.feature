Feature: Player Movement
  As a player
  I want to move my character
  So that I can navigate the game world

  Scenario: Moving the player forward
    Given the player starts at position 0
    When the player moves forward by 5 units
    Then the player's position should be 5