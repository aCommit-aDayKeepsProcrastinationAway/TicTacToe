// TO DO: Implement a menu
// TO DO: After the game is over give a winning screen and options to restart/quit
// TO DO: Highlight winning row
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>


int PositionLocator(int &x, int &y);        // Places Tic's and Tac's in specific places and returns the cell in which it was placed
int WinCondition(int *cells);               // Checks win condition
void LoadTextures(sf::Texture texture_bank[4]);     // Loads textures outside main
void CreateSprites(sf::Texture texture_bank[4], sf::Sprite sprite_bank[12]);     // Creates sprites outside main

int main()
{
    int tic_count = 0, tac_count = 0;
    int cells[9] {0};   // 0 - Nothing, 1 - Tic, 2 - Tac;
    bool tic_drawn[5] {false}, tac_drawn[5] {false};
    bool turn = true; // True tic, False tac
    int CurrentCell;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(585, 615), "TicTacToe_v0.01", sf::Style::Titlebar | sf::Style::Close);

    // Initialize textures, assign files and smooth them out
    sf::Texture texture_bank[4];
    LoadTextures(texture_bank);

    // Create sprites and link them with textures
    sf::Sprite sprite_bank[12];
    CreateSprites(texture_bank, sprite_bank);

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
                                    sprite_bank[tic_count+1].setPosition(mPosi.x, mPosi.y);   // Set position of the X
                                    tic_drawn[tic_count] = true;                        // Switch bool to true for drawing
                                    tic_count++;                                        // ++ count to keep track of how many
                                    cells[CurrentCell] = 1;                             // tics or tacs are created
                                }                                                       // Update cell table

                                if (!turn)
                                {
                                    sprite_bank[tac_count+6].setPosition(mPosi.x, mPosi.y);
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
        window.draw(sprite_bank[0]);

        for (int i = 0; i < 5; i++)
        {
            if(tic_drawn[i]) window.draw(sprite_bank[i+1]);
            if(tac_drawn[i]) window.draw(sprite_bank[i+6]);
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
      if       ((cells[0] == 1)&&(cells[1] == 1)&&(cells[2] == 1)) return 1; ///Horizontal 1
      else if  ((cells[3] == 1)&&(cells[4] == 1)&&(cells[5] == 1)) return 2; ///Horizontal 2
      else if  ((cells[6] == 1)&&(cells[7] == 1)&&(cells[8] == 1)) return 3; ///Horizontal 3
      else if  ((cells[0] == 1)&&(cells[3] == 1)&&(cells[6] == 1)) return 4; ///Vertical 1
      else if  ((cells[1] == 1)&&(cells[4] == 1)&&(cells[7] == 1)) return 5; ///Vertical 2
      else if  ((cells[2] == 1)&&(cells[5] == 1)&&(cells[8] == 1)) return 6; ///Vertical 3
      else if  ((cells[0] == 1)&&(cells[4] == 1)&&(cells[8] == 1)) return 7; ///Diagonal 1
      else if  ((cells[2] == 1)&&(cells[4] == 1)&&(cells[6] == 1)) return 8; ///Diagonal 2

      else if  ((cells[0] == 2)&&(cells[1] == 2)&&(cells[2] == 2)) return 9;  ///Horizontal 1
      else if  ((cells[3] == 2)&&(cells[4] == 2)&&(cells[5] == 2)) return 10; ///Horizontal 2
      else if  ((cells[6] == 2)&&(cells[7] == 2)&&(cells[8] == 2)) return 11; ///Horizontal 3
      else if  ((cells[0] == 2)&&(cells[3] == 2)&&(cells[6] == 2)) return 12; ///Vertical 1
      else if  ((cells[1] == 2)&&(cells[4] == 2)&&(cells[7] == 2)) return 13; ///Vertical 2
      else if  ((cells[2] == 2)&&(cells[5] == 2)&&(cells[8] == 2)) return 14; ///Vertical 3
      else if  ((cells[0] == 2)&&(cells[4] == 2)&&(cells[8] == 2)) return 15; ///Diagonal 1
      else if  ((cells[2] == 2)&&(cells[4] == 2)&&(cells[6] == 2)) return 16; ///Diagonal 2

      else  return 0;
}

void LoadTextures(sf::Texture texture_bank[4])      /// 0 - Background, 1 - X, 2 - O, 3 - highlighter
{
    //Loads from files to textures
    assert(texture_bank[0].loadFromFile("Images/background.png", sf::IntRect(0, 0, 585, 615)));
    assert(texture_bank[1].loadFromFile("Images/tic-tac-toe.png", sf::IntRect(25, 16, 52, 58)));
    assert(texture_bank[2].loadFromFile("Images/tic-tac-toe.png", sf::IntRect(122, 17, 55, 60)));
    //Smooths out the textures
    texture_bank[1].setSmooth(true);
    texture_bank[2].setSmooth(true);
}

void CreateSprites(sf::Texture texture_bank[4], sf::Sprite sprite_bank[12]) /// 0 - Background, 1-6 X, 7-10 O, 11 - highlighter
{
    sprite_bank[0].setTexture(texture_bank[0]);         // Background
    for (int i = 0; i < 5; i++)
        sprite_bank[i+1].setTexture(texture_bank[1]);   // X
    for (int i = 0; i < 5; i++)
        sprite_bank[i+6].setTexture(texture_bank[2]);   // O

    // Rezises X and O sprites to be twice as big
    for (int i=1; i < 11; i++)
        sprite_bank[i].setScale(2, 2);

    // Set origin the center of the image, not doing this offsets all visuals, did it this way because placing them from the top left corner is harder
    for (int i = 0; i < 5; i++)
    {
        sprite_bank[i+1].setOrigin(sf::Vector2f(26, 29));
        sprite_bank[i+6].setOrigin(sf::Vector2f(25, 30));
    }
}
