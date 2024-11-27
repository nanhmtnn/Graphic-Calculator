#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "includes/constants/windowConstants.h"
#include "includes/objects/graph.h"
#include "includes/objects/SidePanel.h"
#include "includes/random/random.h"

using namespace std;

int main()
{
    int framerate = 60;

    sf::FloatRect visibleArea;
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "GRAPHING CALCULATOR"
                            );

    window.setFramerateLimit(framerate);

    // call it once, after creating the window
    window.setVerticalSyncEnabled(true);
    //Application runs at the same freq as monitor

    sf::Cursor cursor;

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile(fontPath);   

    sf::Text textBox("", font);

    SidePanel sidePanel(font);
    Graph graph(font);
    graph.sidePanel = &sidePanel;

    bool entering = false;
    
    float width_ratio = GRAPH_WIDTH_RATIO;

    string txt;

    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen())
    {
        window.setFramerateLimit(framerate);
        sf::Time elapsed = clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        
        //pollEvent and waitEvent are the only two functions that can fill event
        while (window.pollEvent(event))//or waitEvent: EVENT LOOP
        {
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                window.close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) 
                {               
                    case 58: // ENTER
                        if (entering) {
                            entering = false;
                            graph.addExpression(txt);
                            txt = "";
                            textBox.setString(txt);
                        } else {
                            entering = true;
                        }
                        break;
                    case 59: // BACKSPACE
                        if (entering&&!txt.empty()) {
                            txt = txt.substr(0, txt.size()-1);
                            textBox.setString(txt);
                        }
                        break;
                    default:
                        break;
                }
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            
            
            
            case sf::Event::TextEntered:
                if (event.text.unicode<128&&event.text.unicode!=8&&entering) {
                    textBox.setString(txt+=static_cast<char>(event.text.unicode));
                }
                break;
            default:
                break;
            }
        }

        // you HAVE TO clear your window on every iteration of this while.
        window.clear();
        graph.draw(window);
        if(entering) window.draw(textBox);


        // y-axis
        sf::Vertex line1[] =
        {
            sf::Vertex(sf::Vector2f(940, 0.f)),
            sf::Vertex(sf::Vector2f(940, SCREEN_HEIGHT))
        };
        // x-axis
        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(0.f, SCREEN_HEIGHT/2.f)),
            sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT/2.f))
        };

        window.draw(line1, 2, sf::Lines); // y-axis
        window.draw(line2, 2, sf::Lines); // x-axis

        
        sidePanel.draw(window);
        window.setView(window.getDefaultView());
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}