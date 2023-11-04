#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World &world, float x, float y) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((1000.f / 2) / SCALE, (15.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 0.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(500.f, 10.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(10.f, 5.f);
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

class Circle {
public:
    Circle(b2World &world, float x, float y) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;
        body = world.CreateBody(&bodydef);

        b2CircleShape shape;
        shape.m_radius = (10.f / 2) / SCALE;

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        circle.setRadius(10.f);
        circle.setFillColor(sf::Color::Blue);
        circle.setOrigin(10.f, 10.f);
    }

    void update() {
        circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        circle.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(circle);
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
    sf::CircleShape circle;
    b2Body *body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Rueda");

    b2Vec2 gravity(0.0f, 9.90f);
    b2World world(gravity);

    Cube cube(world, 0, 600);
    Circle circle(world, 100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                circle.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                circle.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }


            world.Step(1 / 60.f, 8, 3);


            cube.update();
            circle.update();
            window.clear();
            cube.draw(window);
            circle.draw(window);
            window.display();
        }
    }
    return 0;
}