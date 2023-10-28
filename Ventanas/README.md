Para empezar. Para poder hacer la creacion de cubos (o mas figuras) con una nueva ventana sera necesario importar smfh o OpenGL.
El codigo que sera necesario en el CMakeLists.txt es:

cmake_minimum_required(VERSION 3.26)  
project("Nombre")  
  
include(FetchContent)  
set(BUILD_SHARED_LIBS OFF)  
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)  
FETCHCONTENT_MAKEAVAILABLE(SFML)  
  
set(CMAKE_CXX_STANDARD 17)  
  
add_executable("Nombre" main.cpp)  
find_package(box2d CONFIG REQUIRED)  
target_link_libraries("Nombre" PRIVATE box2d::box2d sfml-system sfml-window sfml-graphics sfml-audio)

Lo  primero se importa al codio en la linea 4 el:
include(FetchContent)  
set(BUILD_SHARED_LIBS OFF)  
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)  
FETCHCONTENT_MAKEAVAILABLE(SFML)  

Importa esas librerias que se ocuparan por el Github.

De ahi en la ultima linea exactamente despues de box2d se pone: sfml-system sfml-window sfml-graphics sfml-audio.

Ahora si en Main.cpp se hace:
Primero la clase cubo. Donde pondremos primero el body del collider en este caso una caja dinamica. Luego se le asigna su altura o anchura. Si tiene densidad en el mundo y se le crea la fisica. Luego se le asigna un color y posicion en el mundo:
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
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);  
  
        b2FixtureDef fixturedef;  
        fixturedef.shape = &shape;  
        fixturedef.density = 1.0f;  
        body->CreateFixture(&fixturedef);  
  
        box.setSize(sf::Vector2f(10.f, 10.f));  
        box.setFillColor(sf::Color::Red);  
        box.setOrigin(5.f, 5.f);  
    }


Luego con un Update se crea la posicion y rotacion del cubo en base al cuerpo anterior mente creado y su angulo para que este repite repite su posicion y rotacion actual:
void update() {  
    box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
    box.setRotation(body->GetAngle() * 180 / b2_pi);  
}

Se dibuja el cuadrado en una nueva ventana:
void draw(sf::RenderWindow &win) const {  
    win.draw(box);  
}


Se le asigna su ubicacion:
void resetPosition() {  
    body->SetTransform(b2Vec2(0, 0), body->GetAngle());  
}

Cuando hagamos que pare el cubo se pondra 0 su velocidad:
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


Luego en el int main()
Se renderea la ventana y sus dimensiones, si el mundo tiene gravedad o no, el cubo coordenadas. Luego con un while se le asignan las teclas de movimiento del cubo:


  
int main() {  
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
  
    Cube cube(world, 400, 300);  
  
    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  
                cube.resetPosition();  
            }  
  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {  
                cube.stop();  
            }  
  
            // The Z key event to close the window  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {  
                window.close();  
                return 0; // return from the main function, effectively ending the program  
            }  
        }


Se añade un tiempo al mundo para que repita y borre el anterior cubo y cree uno nuevo con la nueva posición y se vuelve a hacer todo:

 world.Step(1 / 60.f, 8, 3);  
        cube.update();  
  
        window.clear();  
        cube.draw(window);  
        window.display();  
    }  
    return 0;  
}