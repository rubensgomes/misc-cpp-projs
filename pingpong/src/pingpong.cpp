// Copyright (C) 2016 Rubens S. Gomes <rubens.s.gomes@gmail.com>

#include <src/game.hpp>
#include <src/match.hpp>
#include <iostream>
#include <string>

/**
 * Ping pong simulator application
 *
 * @author  Rubens Gomes
 */
int main(int, char**)
{

    std::string dataFile = "data.csv";

    std::cout << "Reading "
              << dataFile
              << " from current directory."
              << std::endl
              << std::endl;

    Game* game = Game::instance(dataFile);

    std::cout << std::endl;
    std::cout << "---------->>> Tournament Started <<<----------" 
              << std::endl;
    std::cout << std::endl;

    // print tournament bracket at beginning
    std::cout << Match::HEADINGS << std::endl;
    std::cout << *game << std::endl;

    game->run();

    std::cout << std::endl;
    std::cout << "---------->>> Tournament Ended <<<----------" 
              << std::endl;
    std::cout << std::endl;

    // print tournament bracket at end
    std::cout << Match::HEADINGS << std::endl;
    std::cout << *game << std::endl;

    return 0;

}


