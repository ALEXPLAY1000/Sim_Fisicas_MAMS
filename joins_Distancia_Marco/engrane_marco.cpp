#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class CubeDistance {
public:
    CubeDistance(b2World &world, float x, float y) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    CubeDistance cube1(world, 400, 300); // Primer cuadrado
    CubeDistance cube2(world, 410, 300); // Segundo cuadrado
    CubeDistance cube3(world, 420, 300); // Tercer cuadrado


    b2DistanceJointDef jointDef;
    jointDef.Initialize(cube1.getBody(), cube2.getBody(), cube1.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());


    b2DistanceJoint* distanceJoint = static_cast<b2DistanceJoint*>(world.CreateJoint(&jointDef));


    b2DistanceJointDef gearJointDef;
    gearJointDef.Initialize(cube2.getBody(), cube3.getBody(), cube2.getBody()->GetWorldCenter(), cube3.getBody()->GetWorldCenter());
    b2DistanceJoint* gearJoint = static_cast<b2DistanceJoint*>(world.CreateJoint(&gearJointDef));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cube1.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cube1.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cube1.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cube1.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
            }

        }

        world.Step(1 / 60.f, 8, 3);
        cube1.update();
        cube2.update();
        cube3.update();
        window.clear();
        cube1.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        window.display();
    }
    return 0;
}
