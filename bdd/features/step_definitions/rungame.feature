Feature: Run Game
  As a user
  I want to run my game
  So i can verify that it opens

  Scenario: Run the game
    Given Run the game for 2 seconds
    When Waiting to exit
    Then The game should exit successfully