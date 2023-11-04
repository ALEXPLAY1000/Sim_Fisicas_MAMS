Para este codigo se usara el codigo anterior de distancias, pero modificando algunas cosas.

Primero se crea el cubo con sus propiedades de colliders, posicion, color, forma, etc.

en el int main se empieza a modificar:
Se crea dos cubos, uno le ponemos al final de las coordenadas "false" para que no se mueva o no sea dinamico. luego se le añade un distancejoint para que no se acerquen o junten.
luego se le asigna igual  a los dos cubos el joint.

Si todo va bien cuando el jugador mueva el cubo uno este respetando la distancia empezara a dar vueltas rotando alrededor del segundo codigo,

despues con un while se le indica las teclas para mover el cubo y luego se actualiza y dibuja la posicion actual al segundo.

#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
  
constexpr float SCALE = 30.0f;  
  
class Cube {  
public:  
    Cube(b2World &world, float x, float y, bool isDynamic = true) {  
        b2BodyDef bodydef;  
        bodydef.position.Set(x / SCALE, y / SCALE);  
        bodydef.type = isDynamic ? b2_dynamicBody : b2_staticBody;  
        body = world.CreateBody(&bodydef);  
  
        b2PolygonShape shape;  
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);  
  
        b2FixtureDef fixturedef;  
        fixturedef.shape = &shape;  
        fixturedef.density = isDynamic ? 1.0f : 0.0f; // Densidad 0 para estático  
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
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Distancia");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
    //se crea dos cubos uno que no se mueva y otro si  
    Cube cube1(world, 400, 300, false);  
    Cube cube2(world, 450, 300);  
  
    b2DistanceJointDef jointDef;  
    jointDef.Initialize(cube1.getBody(), cube2.getBody(), cube1.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());  
    b2DistanceJoint* distanceJoint = static_cast<b2DistanceJoint*>(world.CreateJoint(&jointDef));  
  
    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  
                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  
                cube2.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  
                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  
                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);  
            }  
  
        }  
  
        world.Step(1 / 60.f, 8, 3);  
        cube1.update();  
        cube2.update();  
  
        window.clear();  
        cube1.draw(window);  
        cube2.draw(window);  
        window.display();  
    }  
    return 0;  
}