#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


    int main()
    {
        // Define the gravity vector
        b2Vec2 gravity(0.0f, -1.62f);

        // Construct a world object, which will hold and simulate the rigid bodies
        b2World world(gravity);





        //Shapes:
        //Triangulo figura:
        b2PolygonShape trianglePol;
        //Vertices y coordenadas de la figura
        b2Vec2 verticeTri[3];
        verticeTri[0].Set(0, 0);
        verticeTri[1].Set(10, 0);
        verticeTri[2].Set(5, 10);
        trianglePol.Set(verticeTri, 3);

        //Rectangulo figura:
        b2PolygonShape rectanguloPol;
        //Vertices y coordenadas de la figura
        b2Vec2 verticesPol[4];
        verticesPol[0].Set(0, 0);
        verticesPol[1].Set(20, 0);
        verticesPol[2].Set(20, 10);
        verticesPol[3].Set(0, 10);
        rectanguloPol.Set(verticesPol, 4);

         //Cuadrado
        b2PolygonShape cuadradoPoly;
        //Vertices y coordenadas de la figura
        b2Vec2 verticesCua[4];
        verticesCua[0].Set(0, 0);
        verticesCua[1].Set(10, 0);
        verticesCua[2].Set(10, 10);
        verticesCua[3].Set(0, 10);
        cuadradoPoly.Set(verticesCua, 4);

        //Pentagono
        b2PolygonShape pentagoPoly;
        //Vertices y coordenadas de la figura
        b2Vec2 verticePenta[5];
        verticePenta[0].Set(3, 0);
        verticePenta[1].Set(6, 0);
        verticePenta[2].Set(0, 5);
        verticePenta[3].Set(5, 10);
        verticePenta[4].Set(10, 10);
        pentagoPoly.Set(verticePenta, 5);

        //Hexagono
        b2PolygonShape hexagonoPoly;
        //Vertices y coordenadas de la figura
        b2Vec2 verticeHexa[6];
        verticeHexa[0].Set(3, 0);
        verticeHexa[1].Set(6, 0);
        verticeHexa[2].Set(0, 5);
        verticeHexa[3].Set(3, 10);
        verticeHexa[4].Set(6, 10);
        verticeHexa[5].Set(10, 5);
        hexagonoPoly.Set(verticeHexa, 6);

        //Octagono
        b2PolygonShape octPoly;
        //Vertices y coordenadas de la figura
        b2Vec2 verticesOct[8];
        verticesOct[0].Set(0, 5);
        verticesOct[1].Set(3, 3);
        verticesOct[2].Set(5, 0);
        verticesOct[3].Set(8, 3);
        verticesOct[4].Set(10, 5);
        verticesOct[5].Set(8, 8);
        verticesOct[6].Set(5, 10);
        verticesOct[7].Set(3, 8);
        octPoly.Set(verticesOct, 8);


        // Create a dynamic body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
         //triangulo crea el body
        b2Body* BodyTriangle = world.CreateBody(&bodyDef);

        //Rectangulo crea el body
        b2Body* BodyRect = world.CreateBody(&bodyDef);

        //Rectangulo crea el body
        b2Body* BodyCua = world.CreateBody(&bodyDef);

        //Pentagono crea el body
        b2Body* BodyPenta = world.CreateBody(&bodyDef);

        //Hexagono crea el body
        b2Body* BodyHexagono = world.CreateBody(&bodyDef);

        //Octagono crea el body
        b2Body* BodyOctagono = world.CreateBody(&bodyDef);


        // Add the shape to the body
        BodyTriangle->CreateFixture(&trianglePol, 1);

        BodyRect->CreateFixture(&rectanguloPol, 1);

        BodyCua->CreateFixture(&rectanguloPol, 1);

        BodyPenta->CreateFixture(&rectanguloPol, 1);

        BodyHexagono->CreateFixture(&hexagonoPoly, 1);

        BodyOctagono->CreateFixture(&octPoly, 1);


        // Simulate the world
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo
            std::cout << "Triangulo " << BodyTriangle->GetPosition().x << " " << BodyTriangle->GetPosition().y << std::endl;


        }
        std::cout<<"-------------------------------------"<<std::endl;
        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo

            std::cout << "Rectangulo " << BodyRect->GetPosition().x << " " << BodyRect->GetPosition().y << std::endl;


        }
        std::cout<<"-------------------------------------"<<std::endl;
        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo

            std::cout << "Cuadrado " << BodyCua->GetPosition().x << " " << BodyCua->GetPosition().y << std::endl;


        }
        std::cout<<"-------------------------------------"<<std::endl;
        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo

            std::cout << "Pentangono " << BodyPenta->GetPosition().x << " " << BodyPenta->GetPosition().y << std::endl;


        }
        std::cout<<"-------------------------------------"<<std::endl;
        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo

            std::cout << "Hexagono " << BodyHexagono->GetPosition().x << " " << BodyHexagono->GetPosition().y << std::endl;


        }
        std::cout<<"-------------------------------------"<<std::endl;
        for (int i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            //Se añade la figura en el mundo

            std::cout << "Octagono " << BodyOctagono->GetPosition().x << " " << BodyOctagono->GetPosition().y << std::endl;


        }


        // Remember to clean up
        world.DestroyBody(BodyTriangle);
        world.DestroyBody(BodyRect);
        world.DestroyBody(BodyCua);
        world.DestroyBody(BodyPenta);
        world.DestroyBody(BodyHexagono);
        world.DestroyBody(BodyOctagono);

        return 0;
    }


