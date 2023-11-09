#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World &world, float x, float y, float sizeCubeX, float sizeCubeY, float colisionSizeX, float colisionSizeY, float densidad, bool estatico, sf::Color fillColor) {

        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(estatico == false)
        {
            bodydef.type = b2_dynamicBody;
        }
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((colisionSizeX / 2) / SCALE, (colisionSizeY / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = densidad;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(sizeCubeX, sizeCubeY));
        box.setFillColor(fillColor);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};
class Circle {
public:
    Circle(b2World &world, float x, float y, float densidad, bool estatico, sf::Color fillColor, float radio) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(estatico == false)
        {
            bodydef.type = b2_dynamicBody;
        }

        body = world.CreateBody(&bodydef);

        b2CircleShape shape;
        shape.m_radius = radio/ SCALE;

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = densidad;
        body->CreateFixture(&fixturedef);

        circle.setRadius(radio);
        circle.setFillColor(fillColor);
        circle.setOrigin(10.f, 10.f);
    }

    void update() {
        circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        circle.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(circle);
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::CircleShape circle;
    b2Body *body;
};
class Triangle {
public:
    Triangle(b2World &world, float x, float y, float scaleX, float scaleY, bool estatico, sf::Color fillColor) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(estatico == false)
        {
            bodydef.type = b2_dynamicBody;
        }

        body = world.CreateBody(&bodydef);

        b2Vec2 vertices[3];
        vertices[0].Set(0.0f, -scaleY / SCALE);  // Vertice 1
        vertices[1].Set(scaleX / SCALE, scaleY/ SCALE);  // Vertice 2
        vertices[2].Set(-scaleX / SCALE, scaleY/ SCALE);  // Vertice 3

        b2PolygonShape shape;
        shape.Set(vertices, 3);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 0.0f;
        body->CreateFixture(&fixturedef);

        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0.0f, -scaleY));
        triangle.setPoint(1, sf::Vector2f(scaleX, scaleY));
        triangle.setPoint(2, sf::Vector2f(-scaleX, scaleY));

        triangle.setFillColor(fillColor);
        triangle.setOrigin(0.0f, 0.0f);
    }

    void update() {
        triangle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        triangle.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(triangle);
    }

    b2Body *getBody() {
        return body;
    }
private:
    sf::ConvexShape triangle;
    b2Body *body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Mecanismo solo para tirar un circulo");

    b2Vec2 gravity(0.0f, 0.5f);
    b2World world(gravity);

    //suelo
    Cube cube(world, 0, 400, 500 ,5, 1000, 15, 0, true, sf::Color::White);
    Cube cubeWin(world, 1180, 950, 60 ,10, 100, 10, 0, true, sf::Color::Green);
    Circle circle5(world, 1190, 940, 0.001, false, sf::Color::Magenta, 10);

    //Plataform
    Cube cubePrism(world, 950, 320, 10 ,70, 20, 180, 2, false, sf::Color::Cyan);
    Cube cubePrism2(world, 950, 0, 10 ,1000, 10, 2000, 0, true, sf::Color::White);
    Cube cube6(world, 870, 780, 10 ,100, 2, 200, 0, true, sf::Color::White);

    //Polea
    Cube cube4(world, 1001, 720, 15, 10, 15, 10, 0.01, false, sf::Color::Red);
    Cube cubePolea1(world, 910, 620, 30 ,10, 30, 20, 0.001, false, sf::Color::Red);
    Cube cubePolea2(world, 1000, 820, 30 ,10, 10, 20, 0.001, false,sf::Color::Blue);
    Cube cubePolea3(world, 910, 920, 30 ,10, 20, 20, 0, true, sf::Color::White);
    Cube cubePolea4(world, 1000, 920, 30 ,10, 10, 20, 0, true, sf::Color::White);
    Cube cubePrism3(world, 910, 619, 30 ,10, 60, 20, 0.001, false, sf::Color::Cyan);
    Cube cubePrism4(world, 1000, 790, 30 ,10, 10, 20, 0.005, false, sf::Color::Cyan);

    //Vueltas
    Cube cube2(world, 520, 580, 20 ,20, 0, 0, 0, true, sf::Color::Red);
    Cube cube3(world, 530, 480, 20 ,90, 20, 80, 0.2, false, sf::Color::Red);

    Cube cube5(world, 1000, 320, 20 ,20, 0, 0, 0, true, sf::Color::Yellow);
    Circle circle4(world, 970, 450, 0.2, false, sf::Color::Yellow, 25);

    //Pelotas
    Circle circle2(world, 260, 100, 0.02, false,sf::Color::Green, 10);
    Circle circle3(world, 320, 100, 0.02, false, sf::Color::Red, 10);


    Triangle triangle(world, 1, 368, 130, 30, true, sf::Color::White);

    //Objetos
    Cube cubeCuerpo(world, 65, 95, 40 ,10, 1, 1, 0.5, false, sf::Color::Red);
    Circle rueda(world, 110, 100, 0.1, false, sf::Color::Yellow, 10);
    Circle rueda2(world, 50, 100, 0.1, false, sf::Color::Yellow, 10);
//llantas
    b2DistanceJointDef distanciaAuto;
    distanciaAuto.Initialize(rueda.getBody(), rueda2.getBody(), rueda.getBody()->GetWorldCenter(), rueda2.getBody()->GetWorldCenter());
    world.CreateJoint(&distanciaAuto);

    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.Initialize(rueda.getBody(), cubeCuerpo.getBody(), rueda.getBody()->GetWorldCenter());
    world.CreateJoint(&revoluteJointDef);
    revoluteJointDef.Initialize(rueda2.getBody(), cubeCuerpo.getBody(), rueda2.getBody()->GetWorldCenter());
    world.CreateJoint(&revoluteJointDef);

//vueltas
    b2RevoluteJointDef revoluteJointDef1;
    revoluteJointDef1.Initialize(cube2.getBody(), cube3.getBody(), cube2.getBody()->GetWorldCenter());
    revoluteJointDef1.lowerAngle = -0.25f * b2_pi;
    revoluteJointDef1.upperAngle = 0.25f * b2_pi;
    revoluteJointDef1.enableMotor = true;
    revoluteJointDef1.motorSpeed = 2.0f;
    revoluteJointDef1.maxMotorTorque = 1.0f;
    world.CreateJoint(&revoluteJointDef1);

    b2RevoluteJointDef revoluteJointDef2;
    revoluteJointDef2.Initialize(cube5.getBody(), circle4.getBody(), cube5.getBody()->GetWorldCenter());
    revoluteJointDef2.lowerAngle = -0.25f * b2_pi;
    revoluteJointDef2.upperAngle = 0.25f * b2_pi;
    revoluteJointDef2.enableMotor = false;
    revoluteJointDef2.motorSpeed = 2.0f;
    revoluteJointDef2.maxMotorTorque = 1.0f;
    world.CreateJoint(&revoluteJointDef2);

//PlataformaLimite

    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.Initialize(cubePrism.getBody(), cubePrism2.getBody(), cubePrism2.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
    prismaticJointDef.lowerTranslation = -15.0f;
    prismaticJointDef.upperTranslation = 15.0f;
    prismaticJointDef.enableLimit = true;
    prismaticJointDef.enableMotor = true;
    prismaticJointDef.motorSpeed = 0.7f;
    prismaticJointDef.maxMotorForce = 1.0f;
    world.CreateJoint(&prismaticJointDef);


//Polea
    b2PulleyJointDef jointPulley;
    jointPulley.Initialize(cubePolea1.getBody(),cubePolea2.getBody(),cubePolea3.getBody()->GetWorldCenter(),cubePolea4.getBody()->GetWorldCenter(),cubePolea1.getBody()->GetWorldCenter(),cubePolea2.getBody()->GetWorldCenter(), 1);
    world.CreateJoint(&jointPulley);

    b2PrismaticJointDef prismaticJointDef2;
    prismaticJointDef2.Initialize(cubePrism3.getBody(), cubePolea3.getBody(), cubePrism3.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
    prismaticJointDef2.lowerTranslation = -15.0f;
    prismaticJointDef2.upperTranslation = 15.0f;
    prismaticJointDef2.enableLimit = true;
    world.CreateJoint(&prismaticJointDef2);

    b2PrismaticJointDef prismaticJointDef3;
    prismaticJointDef3.Initialize(cubePrism4.getBody(), cubePolea4.getBody(), cubePrism4.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));
    prismaticJointDef3.lowerTranslation = -15.0f;
    prismaticJointDef3.upperTranslation = 15.0f;
    prismaticJointDef3.enableLimit = true;
    world.CreateJoint(&prismaticJointDef3);


    while (window.isOpen()) {
        sf::Event event;

        world.Step(1 / 60.f, 8, 3);
        cube.update();

        cubePrism.update();
        cubePrism2.update();
        cubeWin.update();

        cube2.update();
        cube3.update();
        cube5.update();
        circle5.update();
        circle4.update();
        cube6.update();

        cubePolea1.update();
        cubePolea2.update();
        cubePolea3.update();
        cubePolea4.update();
        cubePrism3.update();
        cubePrism4.update();

        cubeCuerpo.update();
        rueda.update();
        rueda2.update();
        circle2.update();
        circle3.update();
        cube4.update();

        triangle.update();

        window.clear();
        cube.draw(window);


        cube2.draw(window);
        cube3.draw(window);
        cube5.draw(window);
        circle4.draw(window);
        cubeWin.draw(window);


        cubePolea1.draw(window);
        cubePolea2.draw(window);
        cubePolea3.draw(window);
        cubePolea4.draw(window);
        cubePrism3.draw(window);
        cubePrism4.draw(window);
        cube6.draw(window);

        cubeCuerpo.draw(window);
        rueda.draw(window);
        rueda2.draw(window);
        circle2.draw(window);
        circle5.draw(window);
        circle3.draw(window);
        cube4.draw(window);

        cubePrism.draw(window);
        cubePrism2.draw(window);


        triangle.draw(window);
        window.display();
    }
    return 0;
}