//#include <SFML/Graphics.hpp>
//#include <cmath>
//#include <cstdlib>
//#include <ctime>
//#include <cstdio>    // snprintf
//#include <fstream>   // file handling
//
//// ---------------- CONSTANTS ----------------
//const int WIN_W = 800;
//const int WIN_H = 600;
//
//const float PADDLE_W_ORIGINAL = 100.f;
//const float PADDLE_H = 20.f;
//const float PADDLE_SPEED = 600.f;
//
//const float BALL_R_ORIGINAL = 8.f;
//const float BALL_SPEED = 400.f;
//
//const float POWERUP_DURATION_S = 10.f;
//
//const int BRICK_ROWS = 6;
//const int BRICK_COLS = 10;
//const int MAX_BRICKS = BRICK_ROWS * BRICK_COLS;
//
//const float BRICK_W = 70.f;
//const float BRICK_H = 25.f;
//const float BRICK_SPACING = 5.f;
//const float BRICK_OFFSET_Y = 50.f;
//
//const int MAX_BALLS = 15;
//const int MAX_POWERUPS = 50;
//
//// powerup types
//const int PU_BIG_PADDLE = 0;
//const int PU_BIG_BALL = 1;
//const int PU_MULTI_BALL = 2;
//
//// ---------------- GAME STATE ----------------
//
//// paddle
//float paddleX, paddleY, paddleW;
//
//// balls arrays
//float ballX[MAX_BALLS], ballY[MAX_BALLS], ballR[MAX_BALLS];
//float ballVX[MAX_BALLS], ballVY[MAX_BALLS];
//bool  ballAlive[MAX_BALLS];
//int   ballCount = 0;
//
//// bricks arrays
//float brickX[MAX_BRICKS], brickY[MAX_BRICKS];
//int   brickHits[MAX_BRICKS];
//bool  brickAlive[MAX_BRICKS];
//sf::Color brickColor[MAX_BRICKS];
//int brickCount = 0;
//
//// powerups arrays
//float puX[MAX_POWERUPS], puY[MAX_POWERUPS], puR[MAX_POWERUPS], puVY[MAX_POWERUPS];
//int   puType[MAX_POWERUPS];
//bool  puAlive[MAX_POWERUPS];
//sf::Color puColor[MAX_POWERUPS];
//int powerUpCount = 0;
//
//// flags
//bool gameStarted = false;
//bool gameOver = false;
//bool gameWon = false;
//
//// score/lives/highscore
//int score = 0;
//int lives = 3;
//int highScore = 0;
//
//// timed powerups
//bool bigPaddleActive = false;
//float bigPaddleTimer = 0.f;
//
//bool bigBallActive = false;
//float bigBallTimer = 0.f;
//
//// ---------------- FILE HANDLING ----------------
//void loadHighScore() 
//{
//    std::ifstream in("highscore.txt");
//    if (in)
//        in >> highScore;
//    else
//        highScore = 0;
//}
//
//void saveHighScore()
//{
//    std::ofstream out("highscore.txt");
//    if (out)
//        out << highScore;
//}
//
//// ---------------- COLLISION (RECT-RECT) ----------------
//bool rectIntersect(float ax, float ay, float aw, float ah,float bx, float by, float bw, float bh) 
//{
//    return (ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by);
//}
//
//// ---------------- RESET FUNCTIONS ----------------
//void resetBricks()
//{
//    brickCount = 0;
//
//    sf::Color colors[6] =
//    {
//        sf::Color::Red,
//        sf::Color(255,165,0),
//        sf::Color::Yellow,
//        sf::Color::Green,
//        sf::Color::Cyan,
//        sf::Color::Blue
//    };
//
//    float totalW = BRICK_COLS * (BRICK_W + BRICK_SPACING);
//    float offsetX = (WIN_W - totalW) / 2.f;
//
//    for (int r = 0; r < BRICK_ROWS; r++)
//    {
//        for (int c = 0; c < BRICK_COLS; c++) 
//        {
//            brickX[brickCount] = offsetX + c * (BRICK_W + BRICK_SPACING);
//            brickY[brickCount] = BRICK_OFFSET_Y + r * (BRICK_H + BRICK_SPACING);
//            brickHits[brickCount] = (r < 2) ? 2 : 1;
//            brickAlive[brickCount] = true;
//            brickColor[brickCount] = colors[r % 6];
//            brickCount++;
//        }
//    }
//}
//
//void resetBall()
//{
//    for (int i = 0; i < MAX_BALLS; i++)
//        ballAlive[i] = false;
//
//    ballCount = 1;
//
//    ballR[0] = BALL_R_ORIGINAL;
//    ballX[0] = paddleX + paddleW / 2.f;
//    ballY[0] = paddleY - 20.f;
//    ballVX[0] = 0.f;
//    ballVY[0] = 0.f;
//    ballAlive[0] = true;
//
//    gameStarted = false;
//}
//
//void resetGame() 
//{
//    score = 0;
//    lives = 3;
//    gameOver = false;
//    gameWon = false;
//
//    // reset powerups
//    powerUpCount = 0;
//    for (int i = 0; i < MAX_POWERUPS; i++)
//        puAlive[i] = false;
//
//    bigPaddleActive = false;
//    bigPaddleTimer = 0.f;
//    bigBallActive = false;
//    bigBallTimer = 0.f;
//
//    paddleW = PADDLE_W_ORIGINAL;
//
//    resetBricks();
//    resetBall();
//}
//
//// ---------------- POWERUP FUNCTIONS ----------------
//void spawnPowerUp(float x, float y)
//{
//    if (powerUpCount >= MAX_POWERUPS)
//        return;
//
//    puX[powerUpCount] = x;
//    puY[powerUpCount] = y;
//    puR[powerUpCount] = 10.f;
//    puVY[powerUpCount] = 150.f;
//    puAlive[powerUpCount] = true;
//
//    int roll = std::rand() % 3;
//    puType[powerUpCount] = roll;
//
//    if (roll == PU_BIG_PADDLE)
//        puColor[powerUpCount] = sf::Color::Magenta;
//    else if (roll == PU_BIG_BALL)
//        puColor[powerUpCount] = sf::Color(255, 128, 0);
//    else
//        puColor[powerUpCount] = sf::Color::Cyan;
//
//    powerUpCount++;
//}
//int findAliveBall()
//{
//    for (int i = 0; i < ballCount; i++) 
//    {
//        if (ballAlive[i])
//            return i;
//    }
//    return -1; // none alive
//}
//
//void applyPowerUp(int type)
//{
//    if (type == PU_BIG_PADDLE) 
//    {
//        if (!bigPaddleActive)
//            paddleW = PADDLE_W_ORIGINAL * 1.5f;
//        bigPaddleActive = true;
//        bigPaddleTimer = 0.f;
//    }
//    else if (type == PU_BIG_BALL) 
//    {
//        if (!bigBallActive)
//        {
//            for (int i = 0; i < ballCount; i++)
//                if (ballAlive[i])
//                    ballR[i] = BALL_R_ORIGINAL * 1.5f;
//        }
//        bigBallActive = true;
//        bigBallTimer = 0.f;
//    }
//    else if (type == PU_MULTI_BALL)
//    {
//
//        int origin = findAliveBall();   // <-- pick ANY alive ball
//        if (origin == -1)
//            return;       // no balls alive, do nothing
//
//        for (int k = 0; k < 2; k++)
//        {
//            // find a free (dead) slot to reuse
//            int slot = -1;
//            for (int i = 0; i < MAX_BALLS; i++) 
//            {
//                if (i >= ballCount || !ballAlive[i]) 
//                {
//                    slot = i;
//                    break;
//                }
//            }
//            if (slot == -1)
//                break; // no free slots
//
//            float a = (std::rand() % 360) * 3.14159f / 180.f;
//
//            ballX[slot] = ballX[origin];
//            ballY[slot] = ballY[origin];
//            ballR[slot] = ballR[origin];
//
//            ballVX[slot] = BALL_SPEED * std::cos(a);
//            ballVY[slot] = -std::abs(BALL_SPEED * std::sin(a));
//
//            ballAlive[slot] = true;
//
//            // if we placed beyond current ballCount, extend ballCount
//            if (slot >= ballCount)
//                ballCount = slot + 1;
//        }
//    }
//}
//
//// ---------------- MAIN ----------------
//int main()
//{
//    std::srand((unsigned)std::time(nullptr));
//
//    sf::RenderWindow window(sf::VideoMode({ WIN_W, WIN_H }), "Brick Smash");
//    window.setFramerateLimit(60);
//
//    // font (no std::string)
//    sf::Font font;
//    bool fontLoaded = font.openFromFile("arial.ttf") || font.openFromFile("C:/Windows/Fonts/arial.ttf") || font.openFromFile("DejaVuSans.ttf");
//
//    loadHighScore();
//
//    // paddle init
//    paddleW = PADDLE_W_ORIGINAL;
//    paddleX = WIN_W / 2.f - paddleW / 2.f;
//    paddleY = WIN_H - 50.f;
//
//    resetGame();
//
//    sf::Clock clock;
//
//    while (window.isOpen()) 
//    {
//        float dt = clock.restart().asSeconds();
//        if (dt > 0.1f) 
//            dt = 0.1f;
//
//        // ---------------- EVENTS ----------------
//        while (auto e = window.pollEvent())
//        {
//            if (e->is<sf::Event::Closed>())
//                window.close();
//
//            if (auto* k = e->getIf<sf::Event::KeyPressed>()) 
//            {
//                if (k->code == sf::Keyboard::Key::Space && !gameStarted && !gameOver && !gameWon && ballAlive[0])
//                {
//                    gameStarted = true;
//
//                    float angDeg = -60.f + (std::rand() % 61);
//                    float angRad = angDeg * 3.14159f / 180.f;
//
//                    ballVX[0] = BALL_SPEED * std::sin(angRad);
//                    ballVY[0] = -BALL_SPEED * std::cos(angRad);
//                }
//
//                if (k->code == sf::Keyboard::Key::R) 
//                {
//                    resetGame();
//                }
//            }
//        }
//
//        // ---------------- UPDATE ----------------
//        if (!gameOver && !gameWon)
//        {
//
//            // timed powerups
//            if (bigPaddleActive) 
//            {
//                bigPaddleTimer += dt;
//                if (bigPaddleTimer > POWERUP_DURATION_S) 
//                {
//                    bigPaddleActive = false;
//                    paddleW = PADDLE_W_ORIGINAL;
//                }
//            }
//
//            if (bigBallActive)
//            {
//                bigBallTimer += dt;
//                if (bigBallTimer > POWERUP_DURATION_S) 
//                {
//                    bigBallActive = false;
//                    for (int i = 0; i < ballCount; i++)
//                        if (ballAlive[i])
//                            ballR[i] = BALL_R_ORIGINAL;
//                }
//            }
//
//            // paddle movement
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//            {
//                paddleX -= PADDLE_SPEED * dt;
//                if (paddleX < 0)
//                    paddleX = 0;
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) 
//            {
//                paddleX += PADDLE_SPEED * dt;
//                if (paddleX + paddleW > WIN_W)
//                    paddleX = WIN_W - paddleW;
//            }
//
//            // mouse movement
//            auto mouse = sf::Mouse::getPosition(window);
//            if (mouse.x >= 0 && mouse.x <= WIN_W)
//            {
//                paddleX = mouse.x - paddleW / 2.f;
//                if (paddleX < 0)
//                    paddleX = 0;
//                if (paddleX + paddleW > WIN_W)
//                    paddleX = WIN_W - paddleW;
//            }
//
//            if (gameStarted)
//            {
//                // balls update
//                for (int i = 0; i < ballCount; i++) 
//                {
//                    if (!ballAlive[i]) 
//                        continue;
//
//                    ballX[i] += ballVX[i] * dt;
//                    ballY[i] += ballVY[i] * dt;
//
//                    float r = ballR[i];
//
//                    // wall collisions
//                    if (ballX[i] - r <= 0) 
//                    {
//                        ballX[i] = r;
//                        ballVX[i] = -ballVX[i]; 
//                    }
//                    if (ballX[i] + r >= WIN_W)
//                    {
//                        ballX[i] = WIN_W - r;
//                        ballVX[i] = -ballVX[i];
//                    }
//                    if (ballY[i] - r <= 0) 
//                    {
//                        ballY[i] = r;
//                        ballVY[i] = -ballVY[i];
//                    }
//
//                    // paddle collision
//                    if (ballVY[i] > 0 && rectIntersect(ballX[i] - r, ballY[i] - r, r * 2, r * 2, paddleX, paddleY, paddleW, PADDLE_H)) 
//                    {
//
//                        ballY[i] = paddleY - r;
//
//                        float hitPos = (ballX[i] - paddleX) / paddleW;
//                        if (hitPos < 0.f) 
//                            hitPos = 0.f;
//                        if (hitPos > 1.f) 
//                            hitPos = 1.f;
//
//                        float angDeg = -60.f + hitPos * 120.f;
//                        float angRad = angDeg * 3.14159f / 180.f;
//
//                        float sp = std::sqrt(ballVX[i] * ballVX[i] + ballVY[i] * ballVY[i]);
//                        if (sp < 400.f) 
//                            sp = 400.f;
//                        if (sp > 800.f)
//                            sp = 800.f;
//
//                        ballVX[i] = sp * std::sin(angRad);
//                        ballVY[i] = -sp * std::cos(angRad) * 1.01f;
//                    }
//
//                    // brick collisions
//                    for (int b = 0; b < brickCount; b++) 
//                    {
//                        if (!brickAlive[b]) 
//                            continue;
//
//                        if (rectIntersect(ballX[i] - r, ballY[i] - r, r * 2, r * 2, brickX[b], brickY[b], BRICK_W, BRICK_H))
//                        {
//
//                            brickHits[b]--;
//                            if (brickHits[b] <= 0) 
//                            {
//                                brickAlive[b] = false;
//                                score += 10;
//
//                                if (std::rand() % 4 == 0)
//                                    spawnPowerUp(brickX[b] + BRICK_W / 2, brickY[b] + BRICK_H / 2);
//                            }
//                            else 
//                            {
//                                sf::Color c = brickColor[b];
//                                brickColor[b] = sf::Color(c.r * 0.7f, c.g * 0.7f, c.b * 0.7f);
//                            }
//
//                            // bounce
//                            float overlapLeft = (ballX[i] + r) - brickX[b];
//                            float overlapRight = (brickX[b] + BRICK_W) - (ballX[i] - r);
//                            float overlapTop = (ballY[i] + r) - brickY[b];
//                            float overlapBottom = (brickY[b] + BRICK_H) - (ballY[i] - r);
//
//                            bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
//                            bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);
//
//                            float minX = fromLeft ? overlapLeft : overlapRight;
//                            float minY = fromTop ? overlapTop : overlapBottom;
//
//                            if (minX < minY) 
//                                ballVX[i] = -ballVX[i];
//                            else           
//                                ballVY[i] = -ballVY[i];
//
//                            break;
//                        }
//                    }
//
//                    // ball falls out
//                    if (ballY[i] - r > WIN_H) 
//                        ballAlive[i] = false;
//                }
//
//                // check alive balls
//                int aliveBalls = 0;
//                for (int i = 0; i < ballCount; i++)
//                    if (ballAlive[i])
//                        aliveBalls++;
//
//                if (aliveBalls == 0)
//                {
//                    lives--;
//
//                    if (lives <= 0) 
//                    {
//                        gameOver = true;
//                        if (score > highScore) 
//                        {
//                            highScore = score;
//                            saveHighScore();
//                        }
//                    }
//                    else
//                    {
//                        bigPaddleActive = false;
//                        bigBallActive = false;
//                        powerUpCount = 0;
//                        paddleW = PADDLE_W_ORIGINAL;
//                        resetBall();
//                    }
//                }
//
//                // powerups update
//                for (int i = 0; i < powerUpCount; i++) 
//                {
//                    if (!puAlive[i])
//                        continue;
//
//                    puY[i] += puVY[i] * dt;
//
//                    if (rectIntersect(puX[i] - puR[i], puY[i] - puR[i], puR[i] * 2, puR[i] * 2, paddleX, paddleY, paddleW, PADDLE_H)) 
//                    {
//                        applyPowerUp(puType[i]);
//                        puAlive[i] = false;
//                    }
//
//                    if (puY[i] - puR[i] > WIN_H)
//                        puAlive[i] = false;
//                }
//
//                // win check
//                bool bricksLeft = false;
//                for (int i = 0; i < brickCount; i++)
//                    if (brickAlive[i])
//                    {
//                        bricksLeft = true;
//                        break;
//                    }
//
//                if (!bricksLeft)
//                {
//                    gameWon = true;
//                    if (score > highScore)
//                    {
//                        highScore = score;
//                        saveHighScore();
//                    }
//                }
//            }
//            else
//            {
//                // ball follows paddle
//                if (ballAlive[0]) 
//                {
//                    ballX[0] = paddleX + paddleW / 2;
//                    ballY[0] = paddleY - 15.f;
//                }
//            }
//        }
//
//        // ---------------- DRAW ----------------
//        window.clear(sf::Color(20, 20, 40));
//
//        // bricks
//        for (int i = 0; i < brickCount; i++)
//        {
//            if (!brickAlive[i])
//                continue;
//            sf::RectangleShape rect({ BRICK_W, BRICK_H });
//            rect.setPosition({ brickX[i], brickY[i] });
//            rect.setFillColor(brickColor[i]);
//            rect.setOutlineColor(sf::Color::Black);
//            rect.setOutlineThickness(2);
//            window.draw(rect);
//        }
//
//        // paddle
//        sf::RectangleShape pshape({ paddleW, PADDLE_H });
//        pshape.setPosition({ paddleX, paddleY });
//        pshape.setFillColor(sf::Color::White);
//        window.draw(pshape);
//
//        // powerups
//        for (int i = 0; i < powerUpCount; i++) 
//        {
//            if (!puAlive[i]) 
//                continue;
//            sf::CircleShape c(puR[i]);
//            c.setPosition({ puX[i] - puR[i], puY[i] - puR[i] });
//            c.setFillColor(puColor[i]);
//            c.setOutlineColor(sf::Color::White);
//            c.setOutlineThickness(2);
//            window.draw(c);
//        }
//
//        // balls
//        for (int i = 0; i < ballCount; i++)
//        {
//            if (!ballAlive[i]) 
//                continue;
//            sf::CircleShape c(ballR[i]);
//            c.setPosition({ ballX[i] - ballR[i], ballY[i] - ballR[i] });
//            c.setFillColor(sf::Color::White);
//            window.draw(c);
//        }
//
//        // UI
//        if (fontLoaded) 
//        {
//            char buf[64];
//
//            std::snprintf(buf, sizeof(buf), "Score: %d", score);
//            sf::Text scoreText(font, buf, 24);
//            scoreText.setPosition({ 10,10 });
//            window.draw(scoreText);
//
//            std::snprintf(buf, sizeof(buf), "Lives: %d", lives);
//            sf::Text livesText(font, buf, 24);
//            livesText.setPosition({ WIN_W - 120.f,10 });
//            window.draw(livesText);
//
//            std::snprintf(buf, sizeof(buf), "High Score: %d", highScore);
//            sf::Text highText(font, buf, 20);
//            highText.setPosition({ WIN_W / 2.f - 80.f,10 });
//            window.draw(highText);
//
//            if (!gameStarted && !gameOver && !gameWon) 
//            {
//                sf::Text t(font, "Press SPACE to launch ball", 20);
//                auto b = t.getLocalBounds();
//                t.setPosition({ WIN_W / 2.f - b.size.x / 2.f, WIN_H / 2.f });
//                t.setFillColor(sf::Color::Yellow);
//                window.draw(t);
//            }
//
//            if (gameOver)
//            {
//                sf::Text t(font, "GAME OVER!", 48);
//                auto b = t.getLocalBounds();
//                t.setPosition({ WIN_W / 2.f - b.size.x / 2.f, WIN_H / 2.f - 50 });
//                t.setFillColor(sf::Color::Red);
//                window.draw(t);
//
//                sf::Text r(font, "Press R to restart", 24);
//                b = r.getLocalBounds();
//                r.setPosition({ WIN_W / 2.f - b.size.x / 2.f, WIN_H / 2.f + 20 });
//                window.draw(r);
//            }
//
//            if (gameWon)
//            {
//                sf::Text t(font, "YOU WIN!", 48);
//                auto b = t.getLocalBounds();
//                t.setPosition({ WIN_W / 2.f - b.size.x / 2.f, WIN_H / 2.f - 50 });
//                t.setFillColor(sf::Color::Green);
//                window.draw(t);
//
//                sf::Text r(font, "Press R to play again", 24);
//                b = r.getLocalBounds();
//                r.setPosition({ WIN_W / 2.f - b.size.x / 2.f, WIN_H / 2.f + 20 });
//                window.draw(r);
//            }
//        }
//
//        window.display();
//    }
//    return 0;
//}