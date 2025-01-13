Feature: Run Game
  As a user
  I want to run my game
  So i can verify that it opens

  Scenario: Run the game
    Given Start the game
    When Run the game
    Then The game should end successfully