En base al codigo de ventana estaves crearemos una forma de que dos cubos no se separen ni se junten con la articulacion  Distancia.

Primero se crea la clase cubo, esto para que sea mas facil manipularlo o encontrar un futuro error, primero le añadimos un collider incluyendo su posicion y tamaño, de ahi la forma y luego hacemos ya la caja que se vera.

En el int main empiezan los cambios.
Añadimos otro cubo para crearlo es
"Cube (nombre del cubo) y sus coordenadas"

Luego se crea una articulacion de distancia con el 
b2DistanceJointDef
luego se instancia o asigna desde el cuerpo o cubo 1 y con quien tiene que tener la misma distancia osea con cubo 2.
para al final crear y desarrollar la distancia.

por ultimo creamos con un while que los cubos se puedan mover y que cada segundo que pase se actualice y dibuje.
En la simulacion saldran ambos cubos pero cuando se mueven se mueve el primero cubo arrastrando al otro causando un efecto como de rotacion.

#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
  
constexpr float SCALE = 30.0f;  
//Creamos la clase cubo  
class Cube {  
public:  
    Cube(b2World &world, float x, float y) {  
        //le asignamos, collider, posicion, rotacion, densidad y demas componentes  
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
//dibujamos  
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
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Rotacion");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
  
    Cube cube1(world, 400, 300);  
    //para crear otros cubos  
    Cube cube2(world, 450, 300);  
    Cube cube3(world, 440, 300);  
  
    // se le añade la articulacion distancia y los asignamos para que no se separen o se acerquen  
    b2DistanceJointDef jointDef;  
    jointDef.Initialize(cube1.getBody(), cube2.getBody(), cube1.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());  
    b2DistanceJoint* distanceJoint = static_cast<b2DistanceJoint*>(world.CreateJoint(&jointDef));  
  
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


