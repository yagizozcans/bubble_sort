//
// Created by Yağız Özcan on 10.03.2024.
//
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

void Game::sRender() {
    s_window.clear();
    for (const auto& line : vertices) {
        s_window.draw(line.data(), line.size(), sf::Lines);
    }
    s_window.display();
}

void Game::sCheckLines() {
    if(i_sorting < s_window.getSize().x - 1)
    {
        j_sorting += 1;
        float a = vertices[j_sorting][1].position.y;
        float b = vertices[j_sorting+1][1].position.y;
        if(a < b)
        {
            vertices[j_sorting][1].position.y = b;
            vertices[j_sorting+1][1].position.y = a;
        }
        if(j_sorting >= s_window.getSize().x - i_sorting - 2)
        {
            j_sorting = 0;
            i_sorting += 1;
        }
    }
}

void Game::run()
{
    s_window.create(sf::VideoMode(600, 150), "My window");

    srand(time(NULL));
    for(int i = 0; i < s_window.getSize().x; i++)
    {
        float random_y =  std::rand() / (float)RAND_MAX * 600;
        std::vector<sf::Vertex> line = {
                sf::Vertex(sf::Vector2f(i, 600.0f), sf::Color::Yellow),
                sf::Vertex(sf::Vector2f(i, 600.0f - random_y), sf::Color::Red)
        };
        vertices.push_back(line);
    }
    while (s_window.isOpen())
    {
        sf::Event event;
        while (s_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                s_window.close();
        }
        sCheckLines();
        sRender();
    }
}
