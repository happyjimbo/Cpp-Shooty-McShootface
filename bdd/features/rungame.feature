Feature: Run Game
  As a user
  I want to run my game
  So i can verify that it opens

  Scenario: Run the game
    Given Game is initalized
    When Run for 2 seconds
    Then The game should exit successfully