// Include important C++ libraries here
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> // for console output

using namespace sf;
sf::Clock gameClock;
sf::Clock timerClock; // separate from gameClock

int rustChoice = 0;
int salvChoice = 0;
int blueChoice = 0;

bool gameOverScreen = false; // to show ending screen
Texture endTexture;
Sprite endSprite;


int main()
{
    // --- Window setup ---
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Scrap", Style::Fullscreen);

    // --- Background ---
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    textureBackground.setSmooth(false);
    Sprite spriteBackground(textureBackground);
    spriteBackground.setScale(0.74f, 0.74f); 

    // --- Frame overlay ---
    Texture textureframe;
    textureframe.loadFromFile("graphics/frame.png");
    textureframe.setSmooth(false);
    Sprite spriteframe(textureframe);
    spriteframe.setScale(0.74f, 0.734f); 

    // --- Claw ---
    Texture textureClaw;
    textureClaw.loadFromFile("graphics/claw.png");
    textureClaw.setSmooth(false);
    Sprite spriteClaw(textureClaw);
    spriteClaw.setScale(0.73f, 0.73f);

    bool clawCloser = false;
    bool sPressed = false;
    bool walkieTalking = false;

    // --- Base coordinates for car stack (bottom to top) ---
    float rustX = 0.f, rustY = 0.f;
    float salvX = 0.f, salvY = 0.f;
    float blueX = 0.f, blueY = 0.f;

    // --- Score ---
    Texture texturescore;
    texturescore.loadFromFile("graphics/score.png");
    texturescore.setSmooth(false);
    Sprite spritescore(texturescore);
    spritescore.setScale(0.74f, 0.74f);

    // --- timer ---
    Texture texturetimer;
    texturetimer.loadFromFile("graphics/timer.png");
    texturetimer.setSmooth(false);
    Sprite spritetimer(texturetimer);
    spritetimer.setScale(0.74f, 0.74f);

    // --- Salvage car textures ---
    Texture salvTex1, salvTex2, salvTex3;
    salvTex1.loadFromFile("graphics/salvagable1.png");
    salvTex2.loadFromFile("graphics/salvagable2.png");
    salvTex3.loadFromFile("graphics/salvagable3.png");
    salvTex1.setSmooth(false);
    salvTex2.setSmooth(false);
    salvTex3.setSmooth(false);

    // --- Blueprint car textures ---
    Texture blueTex1, blueTex2, blueTex3;
    blueTex1.loadFromFile("graphics/blueprint1.png");
    blueTex2.loadFromFile("graphics/blueprint2.png");
    blueTex3.loadFromFile("graphics/blueprint3.png");
    blueTex1.setSmooth(false);
    blueTex2.setSmooth(false);
    blueTex3.setSmooth(false);

    // --- Rust car textures ---
    Texture rustTex1, rustTex2, rustTex3;
    rustTex1.loadFromFile("graphics/rustcar1.png");
    rustTex2.loadFromFile("graphics/rustcar2.png");
    rustTex3.loadFromFile("graphics/rustcar3.png");
    rustTex1.setSmooth(false);
    rustTex2.setSmooth(false);
    rustTex3.setSmooth(false);

    // --- Car Sprites ---
    Sprite salvageCar(salvTex1);   
    salvageCar.setPosition(salvX, salvY);
    salvageCar.setScale(0.74f, 0.74f);

    Sprite blueprintCar(blueTex1); 
    blueprintCar.setPosition(blueX, blueY);
    blueprintCar.setScale(0.74f, 0.74f);

    Sprite rustCar(rustTex1);     
    rustCar.setPosition(rustX, rustY);
    rustCar.setScale(0.74f, 0.74f);

    // --- Walkie Talkie ---
    Texture textureWalkieIdle;
    textureWalkieIdle.loadFromFile("graphics/walkie.png");

    Texture textureWalkieTalk;
    textureWalkieTalk.loadFromFile("graphics/walkieon.png");

    textureWalkieIdle.setSmooth(false);
	textureWalkieTalk.setSmooth(false);
    Sprite spritewalkie(textureWalkieIdle);
    spritewalkie.setPosition(9, 30);
    spritewalkie.setScale(0.71f, 0.71f);

    // --- Wibby Hand ---
    Texture texturewibby;
    texturewibby.loadFromFile("graphics/Wibby.png");
    texturewibby.setSmooth(false);
    Sprite spritewibby(texturewibby);
    spritewibby.setPosition(9, 10);
    spritewibby.setScale(0.74f, 0.74f); 

    // --- Mibby Hand ---
    Texture texturemibby;
	texturemibby.loadFromFile("graphics/Mibby.png");
	texturemibby.setSmooth(false);
	Sprite spritemibby(texturemibby);
	spritemibby.setPosition(9, 10);
	spritemibby.setScale(0.74f, 0.74f); 
    
    // --- Buttons ---
    Texture texturescrapbutton;
    texturescrapbutton.loadFromFile("graphics/scrapbutton.png");
    Sprite spritescrapbutton(texturescrapbutton);
    spritescrapbutton.setPosition(2, -1);
    spritescrapbutton.setScale(0.74f, 0.74f); // fixed scale
    const Vector2f scrapBase(2, -1);

    Texture texturesalvagebutton;
    texturesalvagebutton.loadFromFile("graphics/salvagebutton.png");
    Sprite spritesalvagebutton(texturesalvagebutton);
    spritesalvagebutton.setPosition(5, -1);
    spritesalvagebutton.setScale(0.74f, 0.74f); // fixed scale
    const Vector2f salvageBase(5, -1);

    Texture texturewarrowbutton;
    texturewarrowbutton.loadFromFile("graphics/warrow.png");
    Sprite spritewarrowbutton(texturewarrowbutton);
    spritewarrowbutton.setPosition(3, 2);
    spritewarrowbutton.setScale(0.74f, 0.74f); // fixed scale
    const Vector2f wBase(3, 2);

    Texture texturesarrowbutton;
    texturesarrowbutton.loadFromFile("graphics/sarrow.png");
    Sprite spritesarrowbutton(texturesarrowbutton);
    spritesarrowbutton.setPosition(3, 5);
    spritesarrowbutton.setScale(0.74f, 0.74f); // fixed scale
    const Vector2f sBase(3, 5);

    Texture texturereplenishbutton;
    texturereplenishbutton.loadFromFile("graphics/replenishbutton.png");
    Sprite spritereplenishbutton(texturereplenishbutton);
    spritereplenishbutton.setPosition(5, -2.5);
    spritereplenishbutton.setScale(0.74f, 0.74f); // fixed scale
    const Vector2f replBase(5, -2.5);

    // --- Sounds ---
    SoundBuffer buttonBuffer;
    buttonBuffer.loadFromFile("sound/button_pressing.wav");
    Sound buttonSound;
    buttonSound.setBuffer(buttonBuffer);

    SoundBuffer clawBuffer;
    clawBuffer.loadFromFile("sound/claw_moving.wav");
    Sound clawSound;
    clawSound.setBuffer(clawBuffer);

    SoundBuffer walkieBuffer;
    walkieBuffer.loadFromFile("sound/walkie_talkie.wav");
    Sound walkieSound;
    walkieSound.setBuffer(walkieBuffer);

    SoundBuffer timerBuffer;
    timerBuffer.loadFromFile("sound/timer_running_out.wav");
    Sound timerSound;
    timerSound.setBuffer(timerBuffer);

    // --- Text setup --- 
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    Text scoreText("SCRAP", font, 40);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(20, 20);

    // --- Score text setup ---
    scoreText.setFont(font);
    scoreText.setCharacterSize(65);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(1550, 90); 
    scoreText.setString("0");

    // --- Core variables ---
    int score = 0;

    // Flags to check which car type is currently active
    bool isRust = false;
    bool isSalvage = false;
    bool isBlueprint = true; 
    bool isBlueprintCar = false; 
    bool gameOver = false;

    // Car handling state
    bool carInFront = false;
    bool carProcessed = false;

    // Mibby (the small paw pressing buttons)
    bool mibbyVisible = false;
    sf::Clock mibbyTimer;

    // Wibby (the helper cat grabbing cars)
    bool wibbyVisible = false;
	bool wibbyDragging = false;
    sf::Clock wibbyTimer;

    // Pre-set positions for Wibby’s animation
    Vector2f wibbyStartPos(-120.f, 100.f); 
    Vector2f wibbyGrabPos(800.f, 100.f);     
    Vector2f wibbyExitPos(2500.f, 100.f);    

    // Store the claw’s original position (so it can return after each action)
    Vector2f clawOriginalPos = spriteClaw.getPosition();

    // Store the car’s original position (so it resets properly)
    Vector2f carOriginalPos = blueprintCar.getPosition();

    // Offset used to slightly move buttons when pressed (visual click effect)
    const float pressOffset = 5.f;

    // --- Timer variables ---
    float timeLimit = 60.f;  //total time in seconds          
	float remainingTime = timeLimit;  // initialize remaining time
	sf::Clock timerClock;  // clock to track elapsed time 

    Text timerText;                   
    timerText.setFont(font);
    timerText.setCharacterSize(75);
    timerText.setFillColor(Color::Black);
    timerText.setPosition(150, 265);  

    // --- Claw movement + animation ---
	bool clawActive = false; // is the claw currently moving a car?
	bool clawReturning = false; // is the claw returning to original position?
	bool clawDirectionRight = true; // direction of claw movement

    float timberSpeed = 400.f;
    float clawSpeed = 400.f;
    float moveDistance = 200.f;

	Vector2f clawTargetPos; // target position for claw movement
	Clock clawClock; // clock to track claw movement time

    // --- Car stack tracking ---
	int currentCarIndex = 2; // 0: rust, 1: salvage, 2: blueprint
	Sprite* activeCar = &blueprintCar; // start with blueprint car

    // --- Main loop ---
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

           // --- SPACE: call Wibby to grab the car ---
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
				if (!walkieTalking && carInFront && activeCar != nullptr) // only if a car is in front
                {
                    walkieTalking = true;
                    spritewalkie.setTexture(textureWalkieTalk);
                    walkieSound.play();

                    wibbyVisible = true;
                    wibbyDragging = true; 
                    wibbyTimer.restart();
                    spritewibby.setPosition(wibbyStartPos);

					if (isBlueprint) // correct car
                    {
						int chance = rand() % 10; // 0–9
                        if (chance < 3) // 30% chance bad
                        {
                            int penalty = (rand() % 5) + 1; // smaller loss: 1–5 points
                            score -= penalty;
                            std::cout << "Wibby broke parts! -" << penalty << " points\n";
                        }
                        else // 70% chance good
                        {
                            int bonus = (rand() % 20) + 10; // big reward: 10–30 points
                            score += bonus;
                            std::cout << "Wibby fixed parts! +" << bonus << " points\n";
                        }
                    }
                    else
                    {
						score -= 5; // wrong car
                        std::cout << "Wrong car! -5 points\n";
                    }
                    scoreText.setString(std::to_string(score));
                }

            }

            // --- W: move claw back to pile ---
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::W) 
            {
				if (activeCar != nullptr && clawCloser && !clawActive && !clawReturning) // only if a car is in front
                {
                    clawCloser = false;
                    carInFront = false;
                    carProcessed = false;

                    spriteClaw.setPosition(clawOriginalPos);
                    spriteClaw.setScale(0.74f, 0.74f);

                    activeCar->setScale(0.74f, 0.74f);
                    activeCar->setPosition(carOriginalPos);
                    std::cout << "Returned claw to pile.\n";
                }
                else if (activeCar == nullptr) 
                    std::cout << "No cars available to move! Press R to replenish.\n";
            }

            // --- S: bring car closer ---
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                if (activeCar != nullptr && !clawCloser && !carInFront && !clawActive && !clawReturning)
                {
                    clawCloser = true;
                    carInFront = true;
                    carProcessed = false;

                    spriteClaw.setPosition(clawOriginalPos.x - 900, clawOriginalPos.y - 210); 
                    spriteClaw.setScale(1.5f, 1.5f);
                    activeCar->setScale(1.4f, 1.4f);

                    float offsetX = 0.f;
                    float offsetY = 0.f;

                    if (activeCar == &rustCar)
                    {
                        if (rustChoice == 0) { offsetX = -850.f; offsetY = -80.f; } //rust car 1
                        else if (rustChoice == 1) { offsetX = -950.f; offsetY = -450.f; } //rust car 2
                        else if (rustChoice == 2) { offsetX = -890.f; offsetY = 150.f; } //rust car 3
                    }
                    else if (activeCar == &salvageCar)
                    {
						if (salvChoice == 0) { offsetX = -950.f; offsetY = -450.f; } //salvage car 1
						else if (salvChoice == 1) { offsetX = -850.f; offsetY = -270.f; } //salvage car 2
						else if (salvChoice == 2) { offsetX = -850.f; offsetY = -20.f; } //salvage car 3
                    }
                    else if (activeCar == &blueprintCar)
                    {
						if (blueChoice == 0) { offsetX = -950.f; offsetY = 70.f; } //blueprint car 1
						else if (blueChoice == 1) { offsetX = -850.f; offsetY = -200.f; } //blueprint car 2
						else if (blueChoice == 2) { offsetX = -850.f; offsetY = -450.f; } //blueprint car 3
                    }                

                    carOriginalPos = activeCar->getPosition();
					activeCar->setPosition(carOriginalPos.x + offsetX, carOriginalPos.y + offsetY); // move car in front of claw

                    std::cout << "Active car: Blueprint, blueChoice = " << blueChoice 
                        << " | Using offsetX = " << offsetX << " offsetY = " << offsetY << std::endl; 

                    std::cout << "Active car: salvage, salvChoice = " << salvChoice
						<< " | Using offsetX = " << offsetX << " offsetY = " << offsetY << std::endl;

					std::cout << "Active car: rust, rustChoice = " << rustChoice 
                        << " | Using offsetX = " << offsetX << " offsetY = " << offsetY << std::endl;
                }
                else if (activeCar == nullptr)
                {
					std::cout << "No cars available to move! Press R to replenish.\n";
                }
            }
  
           // --- A: scrap car ---
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::A)
            {
                if (activeCar != nullptr && carInFront && !carProcessed && !clawActive && !clawReturning)
                {
                    clawActive = true;
                    clawDirectionRight = false;
					clawTargetPos = { spriteClaw.getPosition().x - moveDistance, spriteClaw.getPosition().y }; // move left
                    std::cout << "Scrapping car...\n";
                    clawSound.play();

                    // Simple scoring
                    if (isRust)
                        score += 10;   // correct
                    else if (isSalvage)
                        score -= 5;    // wrong
                    else if (isBlueprint)
                        score -= 25;   // bad idea!

                    scoreText.setString(std::to_string(score));  // update score display
                } 
                
            }

            // --- D: salvage car ---
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::D)
            {
                if (activeCar != nullptr && carInFront && !carProcessed && !clawActive && !clawReturning)
                {
                    clawActive = true;
                    clawDirectionRight = true;
					clawTargetPos = { spriteClaw.getPosition().x + moveDistance, spriteClaw.getPosition().y }; // move right
                    std::cout << "Salvaging car...\n";
                    clawSound.play();
              
                    if (isSalvage)
                        score += 20;   
                    else if (isRust)
                        score -= 5;   
                    else if (isBlueprint)
                        score += 10;  

					scoreText.setString(std::to_string(score));
                }
                
            }

           // --- R: replenish pile ---
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
            {
                std::cout << "Replenishing new pile!\n";

                // --- visually aligned car positions ---
                rustCar.setPosition(0.f, 5.f);      // bottom car
                salvageCar.setPosition(5.f, 0.f);   // middle car
                blueprintCar.setPosition(0.f, 5.f); // top car

                // --- Slight rotation ---
                rustCar.setRotation(-3.f);
                salvageCar.setRotation(2.f);
                blueprintCar.setRotation(-2.f);

                // --- Scale ---
                rustCar.setScale(0.74f, 0.74f);
                salvageCar.setScale(0.74f, 0.74f);
                blueprintCar.setScale(0.74f, 0.74f);

                // --- Randomize textures ---
                rustChoice = rand() % 3;
                salvChoice = rand() % 3;
                blueChoice = rand() % 3;

                if (rustChoice == 0) rustCar.setTexture(rustTex1);
                else if (rustChoice == 1) rustCar.setTexture(rustTex2);
                else rustCar.setTexture(rustTex3);

                if (salvChoice == 0) salvageCar.setTexture(salvTex1);
                else if (salvChoice == 1) salvageCar.setTexture(salvTex2);
                else salvageCar.setTexture(salvTex3);

                if (blueChoice == 0) blueprintCar.setTexture(blueTex1);
                else if (blueChoice == 1) blueprintCar.setTexture(blueTex2);
                else blueprintCar.setTexture(blueTex3);

                // --- Layer effect (bottom cars faded) ---
                rustCar.setColor(Color(255, 255, 255, 120));
                salvageCar.setColor(Color(255, 255, 255, 170));
                blueprintCar.setColor(Color(255, 255, 255, 255));

                // --- Reset logic ---
				currentCarIndex = 2; // start with blueprint car
				activeCar = &blueprintCar; 

                isRust = false;
                isSalvage = false;
                isBlueprint = true;

                clawCloser = false;
                carProcessed = false;
                carInFront = false;

                carOriginalPos = activeCar->getPosition();

                std::cout << "New pile stacked cleanly.\n";
            }

        }
    
        // --Claw movement based on timberr !!--
		float dt = gameClock.restart().asSeconds(); // delta time
		remainingTime = timeLimit - timerClock.getElapsedTime().asSeconds(); // update remaining time
		if (remainingTime < 0) // prevent negative time
			remainingTime = 0; 

        // --- Walkie auto turn-off after 3 seconds ---
		if (walkieTalking && wibbyTimer.getElapsedTime().asSeconds() >= 3.f) // 3 seconds walkie time
        {
            walkieTalking = false;
            spritewalkie.setTexture(textureWalkieIdle);
            wibbyVisible = false;
            wibbyDragging = false;
            std::cout << "Walkie: Wibby done.\n";
        }

        // --- Wibby quick grab logic ---
        if (wibbyDragging && activeCar != nullptr)
        {
            // Stay visible for a short time
            float visibleTime = 0.8f;

            //  Keep Wibby fixed near the walkie area
            spritewibby.setPosition(170.f, 150.f); 

            // Flicker animation (on/off every 0.1 second)
            if (static_cast<int>(wibbyTimer.getElapsedTime().asMilliseconds() / 100) % 2 == 0)
                spritewibby.setColor(Color::White);
            else
                spritewibby.setColor(Color(255, 255, 255, 120));

            // Hide after visibleTime seconds
            if (wibbyTimer.getElapsedTime().asSeconds() > visibleTime)
            {
                wibbyDragging = false;
                wibbyVisible = false;
                carProcessed = true;
                carInFront = false;

                activeCar->setColor(Color(255, 255, 255, 0)); // hide car
                std::cout << "Wibby popped in and took the car!\n";

                // Reset claw
                spriteClaw.setPosition(clawOriginalPos);
                spriteClaw.setScale(0.74f, 0.74f);
                clawCloser = false;

                // Move to next car
                currentCarIndex--;

                if (currentCarIndex < 0)
                {
                    std::cout << "All cars processed! Press R to replenish.\n";
					currentCarIndex = -1; // no cars left
					activeCar = nullptr; // no active car
                }
                else
                {
                    // Switch active car
                    if (currentCarIndex == 2) activeCar = &blueprintCar;
                    if (currentCarIndex == 1) activeCar = &salvageCar;
                    if (currentCarIndex == 0) activeCar = &rustCar;

                    // Update flags
                    isRust = (activeCar == &rustCar);
                    isSalvage = (activeCar == &salvageCar);
                    isBlueprint = (activeCar == &blueprintCar);

                    // Reset new car visuals
                    activeCar->setColor(Color::White);
                    activeCar->setScale(0.74f, 0.74f);
                    if (activeCar == &blueprintCar) activeCar->setPosition(blueX, blueY);
                    else if (activeCar == &salvageCar) activeCar->setPosition(salvX, salvY);
                    else if (activeCar == &rustCar) activeCar->setPosition(rustX, rustY);

                    // Reset claw state
                    clawCloser = false;
                    carProcessed = false;
                    carInFront = false;
                    carOriginalPos = activeCar->getPosition();

                    std::cout << "Next car ready (Wibby auto-switch).\n";
                }
            }
        }


        // --- Update countdown timer ---
		remainingTime -= dt; // decrease remaining time
        if (remainingTime <= 10.f && remainingTime > 9.5f)  // play once near end
        {
            timerSound.play();
        }
		if (remainingTime <= 0 && !gameOver) // time's up
        {
            gameOver = true;
            std::cout << "Shift complete! Final score: " << score << "\n";

            // --- Pick ending screen based on score ---
            if (score < 150)
                endTexture.loadFromFile("graphics/end_low.png");
            else if (score < 350)
                endTexture.loadFromFile("graphics/end_mid.png");
            else
                endTexture.loadFromFile("graphics/end_high.png");

            endSprite.setTexture(endTexture);
            endSprite.setScale(0.74f, 0.74f);

            // --- End screen mode ---
            while (window.isOpen())
            {
                Event e;
				while (window.pollEvent(e)) // handle events
                {
					if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) // exit on ESC
                        window.close();
                }

                window.clear();
                window.draw(endSprite);

                // Text overlay showing score
                Text endText;
                endText.setFont(font);
                endText.setCharacterSize(65);
                endText.setFillColor(Color::Black);
				endText.setString("Shift Complete!\nFinal Score: " + std::to_string(score) + "\n\nPress ESC to Exit"); // show final score        
                endText.setPosition(310, 50);
                window.draw(endText);
                window.display();
            }
        }

        // Convert to minutes:seconds (digital style)
		int minutes = static_cast<int>(remainingTime) / 60; // 120 to 2 minutes, for example
		int seconds = static_cast<int>(remainingTime) % 60; // Remainder gives leftover seconds

        // Format it like 0:59 or 1:00
        std::ostringstream timeStream;

        // If seconds are below 10, add a "0" in front to keep it two digits
        if (seconds < 10)
            timeStream << minutes << ":0" << seconds;
        else
            timeStream << minutes << ":" << seconds;
        timerText.setString(timeStream.str());

		// --- Claw active movement ---
        if (clawActive && carInFront && !carProcessed)
        {
            float moveAmount;
            if (clawDirectionRight)
            {
                // move right (positive direction)
                moveAmount = timberSpeed * dt;
            }
            else
            {
                // move left (negative direction)
                moveAmount = -timberSpeed * dt;
            }
            spriteClaw.move(moveAmount, 0);
            activeCar->move(moveAmount, 0);

            // stop once target reached
            bool reachedTarget = false;

            if (clawDirectionRight)
            {
                // Moving right
                if (spriteClaw.getPosition().x >= clawTargetPos.x)
                {
                    reachedTarget = true;
                }
            }
            else
            {
                // Moving left
                if (spriteClaw.getPosition().x <= clawTargetPos.x)
                {
                    reachedTarget = true;
                }
            }

            // This is what happens when claw is at its target
            if (reachedTarget)
            {
                clawActive = false;
                carProcessed = true;
                carInFront = false;

				activeCar->setColor(Color(255, 255, 255, 0)); // hide car            
                sf::sleep(sf::milliseconds(150)); // small delay

                spriteClaw.setPosition(clawOriginalPos); 
                spriteClaw.setScale(0.74f, 0.74f);
                clawCloser = false; 

                // Move to next car in the pile
                currentCarIndex--; 

                if (currentCarIndex < 0)
                {
                    std::cout << "All cars processed! Press r to replenish.\n";
                    currentCarIndex = -1;
                    activeCar = nullptr;
                }
                else
                {
                    // Switch active car pointer
                    if (currentCarIndex == 2) activeCar = &blueprintCar;
                    if (currentCarIndex == 1) activeCar = &salvageCar;
                    if (currentCarIndex == 0) activeCar = &rustCar;

                    isRust = (activeCar == &rustCar);
                    isSalvage = (activeCar == &salvageCar);
                    isBlueprint = (activeCar == &blueprintCar);

                    // Reset its transform properly (this is the fix!)
                    activeCar->setColor(Color::White);
                    activeCar->setScale(0.74f, 0.74f);     // normal pile scale again
                    if (activeCar == &blueprintCar) activeCar->setPosition(blueX, blueY);
                    else if (activeCar == &salvageCar) activeCar->setPosition(salvX, salvY);
                    else if (activeCar == &rustCar) activeCar->setPosition(rustX, rustY);

                    // Make sure claw resets too
                    clawCloser = false;
                    carProcessed = false;
                    carInFront = false;

                    // Update stored base position for new car
                    carOriginalPos = activeCar->getPosition();

                    std::cout << "Next car ready.\n";
                }

            }
        }
        
        // --- BUTTON PRESS VISUALS ---
        if (Keyboard::isKeyPressed(Keyboard::A) ||
            Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::W) ||
            Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::R))
        {
            buttonSound.play();
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            spritescrapbutton.setPosition(scrapBase.x, scrapBase.y + pressOffset);
            spritescrapbutton.setColor(Color(200, 200, 200));

            mibbyVisible = true;
            spritemibby.setPosition(10, 60);
        }
        else
        {
            spritescrapbutton.setPosition(scrapBase);
            spritescrapbutton.setColor(Color::White);
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            spritesalvagebutton.setPosition(salvageBase.x, salvageBase.y + pressOffset);
            spritesalvagebutton.setColor(Color(200, 200, 200));

            mibbyVisible = true;
            spritemibby.setPosition(970, 40);
        }
        else
        {
            spritesalvagebutton.setPosition(salvageBase);
            spritesalvagebutton.setColor(Color::White);
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            spritewarrowbutton.setPosition(wBase.x, wBase.y + pressOffset);
            spritewarrowbutton.setColor(Color(200, 200, 200));

            mibbyVisible = true;
            spritemibby.setPosition(520, 90);
        }
        else
        {
            spritewarrowbutton.setPosition(wBase);
            spritewarrowbutton.setColor(Color::White);
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            spritesarrowbutton.setPosition(sBase.x, sBase.y + pressOffset);
            spritesarrowbutton.setColor(Color(200, 200, 200));

            mibbyVisible = true;
            spritemibby.setPosition(520, 190);
        }
        else
        {
            spritesarrowbutton.setPosition(sBase);
            spritesarrowbutton.setColor(Color::White);
        }

        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            spritereplenishbutton.setPosition(replBase.x, replBase.y + pressOffset);
            spritereplenishbutton.setColor(Color(200, 200, 200));

            mibbyVisible = true;
            spritemibby.setPosition(1270, 160);
        }
        else
        {
            spritereplenishbutton.setPosition(replBase);
            spritereplenishbutton.setColor(Color::White);
        }
        if (!Keyboard::isKeyPressed(Keyboard::A) && 
            !Keyboard::isKeyPressed(Keyboard::D) &&
            !Keyboard::isKeyPressed(Keyboard::W) &&
            !Keyboard::isKeyPressed(Keyboard::S) &&
            !Keyboard::isKeyPressed(Keyboard::R))
        {
            mibbyVisible = false;
        }

		// --drawings--
        window.clear();

        // background
        window.draw(spriteBackground);

        // draw all cars
        window.draw(blueprintCar);
        window.draw(salvageCar);
        window.draw(rustCar);

        // draw the active one again 
        if (activeCar != nullptr)
            window.draw(*activeCar);

        //Wibby hand
        if (wibbyVisible) window.draw(spritewibby);

        // frame
        window.draw(spriteframe); 

        // claw
        window.draw(spriteClaw);

        //score + timer
        window.draw(spritescore);
        window.draw(spritetimer);
        window.draw(timerText);

        //Ui elements!!
        window.draw(spritescrapbutton);
        window.draw(spritesalvagebutton);
        window.draw(spritewarrowbutton);
        window.draw(spritesarrowbutton);
        window.draw(spritereplenishbutton);
        window.draw(spritewalkie);

        //Mibby hand
        if (mibbyVisible) window.draw(spritemibby);

        //text
        window.draw(scoreText);
        window.display();
    }
    return 0;
}
