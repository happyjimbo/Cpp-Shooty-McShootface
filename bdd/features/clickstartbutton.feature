Feature: Click start button
  As a user
  I want to start the game
  So i can verify that it the transitions from the title screen to the game

  Scenario: Click the start button
    When Game is initalized
    When Click x:527 and y:435 to start the game
    Then The game should exit successfully