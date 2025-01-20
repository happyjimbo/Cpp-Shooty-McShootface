Feature: Move the player
  As a user
  I want to start the game and move the player
  So i can verify that the controls work

  Scenario: Moving the player
    When Game is initalized
    When Move player
    Then The game should exit successfully