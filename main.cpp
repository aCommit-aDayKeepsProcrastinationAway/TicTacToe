// TO DO: Implement a menu
// TO DO: After the game is over give a winning screen and options to restart/quit
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>

int PositionLocator(int &x, int &y);        // Places Tic's and Tac's in specific places and returns the cell in which it was placed
int WinCondition(int *cells);               // Checks win condition

int main()
{
    int tic_count = 0, tac_count = 0;
    int cells[9] {0};   // 0 - Nothing, 1 - Tic, 2 - Tac;
    bool tic_drawn[5] {false}, tac_drawn[5] {false};
    bool turn = true; // True tic, False tac
    int CurrentCell;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(585, 615), "TicTacToe_v0.01", sf::Style::Titlebar | sf::Style::Close);

    // Initialize textures
    sf::Texture txt_background; assert(txt_background.loadFromFile("Images/background.png", sf::IntRect(0, 0, 585, 615)));
    sf::Texture txt_tic;  assert(txt_tic.loadFromFile("Images/tic-tac-toe.png", sf::IntRect(25, 16, 52, 58)));
    sf::Texture txt_tac; assert(txt_tac.loadFromFile("Images/tic-tac-toe.png", sf::IntRect(122, 17, 55, 60)));

    // Smooth out the textures for scaling
    txt_tic.setSmooth(true);
    txt_tac.setSmooth(true);

    // Create sprites for textures
    sf::Sprite spr_background;
    sf::Sprite spr_tic[5];
    sf::Sprite spr_tac[5];

    // Set origin the center of the image
    for (int i = 0; i < 5; i++)
    {
        spr_tic[i].setOrigin(sf::Vector2f(26, 29));
        spr_tac[i].setOrigin(sf::Vector2f(25, 30));
    }

    // Assign textures for sprites and enlarge sprites
    spr_background.setTexture(txt_background);

    for (int i=0; i < 5; i++)
    {
        spr_tic[i].setTexture(txt_tic);
        spr_tac[i].setTexture(txt_tac);

        spr_tic[i].setScale(2, 2);
        spr_tac[i].setScale(2, 2);
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Clear window to display a new frame
        window.clear();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // Close window: exit
                case sf::Event::Closed:
                    window.close();
                    break;

                // Register mouse left clicks
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mPosi = sf::Mouse::getPosition(window);        // Get mouse position
                        CurrentCell = PositionLocator(mPosi.x, mPosi.y);            // Assign it to a specific square and track positions taken

                        if (WinCondition(cells) == 0)
                        {
                            if (cells[CurrentCell] == 0)                                // Check if cell is taken
                            {
                                if (turn)
                                {                                                       // Actions during a turn:
                                    spr_tic[tic_count].setPosition(mPosi.x, mPosi.y);   // Set position of the X
                                    tic_drawn[tic_count] = true;                        // Switch bool to true for drawing
                                    tic_count++;                                        // ++ count to keep track of how many
                                    cells[CurrentCell] = 1;                             // tics or tacs are created
                                }                                                       // Update cell table

                                if (!turn)
                                {
                                    spr_tac[tac_count].setPosition(mPosi.x, mPosi.y);
                                    tac_drawn[tac_count] = true;
                                    tac_count++;
                                    cells[CurrentCell] = 2;
                                }

                                turn = !turn;       // Turn flipper
                            }

                        }

                        else                // End game screen
                        {

                        }
                    }

                    break;
            }

        }

        /* The main problem with the program is that most of the game loop is under sf::Mouse::Left button event. That means
         * that after the game is over you need to keep triggering sf::Mouse::Left event to progress to the end screen.
         * While some games do this it isn't intuitive and leaves the player confused thinking the game is bugged.
         * To avoid this I need to implement a conditional outside of the event loop that checks for the winning condition
         * and if condition is satisfied, draws graphics to tell the player how to proceed or how to quit.*/

        // Always draw background
        window.draw(spr_background);

        for (int i = 0; i < 5; i++)
        {
            if(tic_drawn[i]) window.draw(spr_tic[i]);
            if(tac_drawn[i]) window.draw(spr_tac[i]);
        }

        //Display drawn sprites
        window.display();

    }
    return EXIT_SUCCESS;
}

int PositionLocator(int &x, int &y) {
    int cell = 0;

    if ((x < 200) && (y < 216))            /// 1st Cell : 116, 129
    {
        x = 116;
        y = 129;
    }
    else if ((x < 370) && (y < 215))       /// 2nd Cell : 286, 129
    {
        x = 286;
        y = 129;
        cell = 1;
    }
    else if ((x < 584) && (y < 215))       /// 3rd Cell : 457, 129
    {
        x = 457;
        y = 129;
        cell = 2;
    }
    else if ((x < 200) && (y < 389))       /// 4th Cell : 116, 309
    {
        x = 116;
        y = 309;
        cell = 3;
    }
    else if ((x < 370) && (y < 389))       /// 5th Cell : 286, 309
    {
        x = 286;
        y = 309;
        cell = 4;
    }
    else if ((x < 584) && (y < 389))       /// 6th Cell : 457, 309
    {
        x = 457;
        y = 309;
        cell = 5;
    }
    else if ((x < 200) && (y < 616))       /// 7th Cell : 116, 476
    {
        x = 116;
        y = 476;
        cell = 6;
    }
    else if ((x < 370) && (y < 616))       /// 8th Cell : 286, 476
    {
        x = 286;
        y = 476;
        cell = 7;
    }
    else if ((x < 584) && (y < 616))       /// 9th Cell : 457, 476
    {
        x = 457;
        y = 476;
        cell = 8;
    }

    return cell;
}

int WinCondition(int *cells) // (Tic won if 1-8 is returned, Tac if 9-16)
{
      if       ((cells[0] == 1)&&(cells[1] == 1)&&(cells[2] == 1)) return 1; //Horizontal 1
      else if  ((cells[3] == 1)&&(cells[4] == 1)&&(cells[5] == 1)) return 2; //Horizontal 2
      else if  ((cells[6] == 1)&&(cells[7] == 1)&&(cells[8] == 1)) return 3; //Horizontal 3
      else if  ((cells[0] == 1)&&(cells[3] == 1)&&(cells[6] == 1)) return 4; //Vertical 1
      else if  ((cells[1] == 1)&&(cells[4] == 1)&&(cells[7] == 1)) return 5; //Vertical 2
      else if  ((cells[2] == 1)&&(cells[5] == 1)&&(cells[8] == 1)) return 6; //Vertical 3
      else if  ((cells[0] == 1)&&(cells[4] == 1)&&(cells[8] == 1)) return 7; //Diagonal 1
      else if  ((cells[2] == 1)&&(cells[4] == 1)&&(cells[6] == 1)) return 8; //Diagonal 2

      else if  ((cells[0] == 2)&&(cells[1] == 2)&&(cells[2] == 2)) return 9;  //Horizontal 1
      else if  ((cells[3] == 2)&&(cells[4] == 2)&&(cells[5] == 2)) return 10; //Horizontal 2
      else if  ((cells[6] == 2)&&(cells[7] == 2)&&(cells[8] == 2)) return 11; //Horizontal 3
      else if  ((cells[0] == 2)&&(cells[3] == 2)&&(cells[6] == 2)) return 12; //Vertical 1
      else if  ((cells[1] == 2)&&(cells[4] == 2)&&(cells[7] == 2)) return 13; //Vertical 2
      else if  ((cells[2] == 2)&&(cells[5] == 2)&&(cells[8] == 2)) return 14; //Vertical 3
      else if  ((cells[0] == 2)&&(cells[4] == 2)&&(cells[8] == 2)) return 15; //Diagonal 1
      else if  ((cells[2] == 2)&&(cells[4] == 2)&&(cells[6] == 2)) return 16; //Diagonal 2

      else  return 0;
}
