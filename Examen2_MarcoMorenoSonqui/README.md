Para este código se necesito parte del código de Ventanas, Esto debido ya que se usara la creación de ventanas y la clase del Cubo.
Primero para este código en la clase Cubo se hizo:
Se añadió los flotantes de
 1) Sizes Cube X/Y: Esto para asignarle los tamaños de la figura.
 2) Size colisión X/Y: Esto para ver que tamaño se ocupa para las colisiones.
 3) Densidad: Se añade un float de densidad para poner cuanta densidad tiene el objeto esto para saber mas o menos su peso
 4) un Bool de estático esto para si esta en verdadero el objeto sea estático si no es dinámico.
 5) Por ultimo para el constructor se añade los colores.

Después asignamos estas variables del constructor a las partes del código.

Después se crea una clase circulo con las variables de posición, densidad, estático, color y el radio del circulo.
Por ultimo se crea la clase del triangulo las cuales tienen la posición, la escala x/y, si es estático y por ultimo el color.

Para el código main primero se crea la ventana. Luego se asigna la gravedad para el mundo. en este caso 0.5f.


Aquí llega la parte de la creación de objetos.
Cada uno crea un Cuadrado, circulo y triangulo, rellenando las variables que pide como la posición (la posición en el mundo), Los Sizes (para asignar sus tamaños tanto de la figura como el de su colisión), Su densidad (si el objeto es estático como para los prismáticos o polea se pone en 0), Y si su objeto es estático (que no se mueve) o dinámico (se puede mover) y por ultimo su color.

Después de sus creaciones llega crear las uniones o los joins.
El primero que sale es el de Distancia la cual se usa primero para que dos circulos que representan como ruedas estén separadas y no se alejen o se acerquen.
Luego se usa la Revolucion para hacer que el cuerpo del auto este conectado a las ruedas y no rote.

Después  se usa  el join de revolucion otra vez pero la diferencia es que usaremos el motor.
Se lo asignamos a dos cubos y esto es para que funcione como un remolino para que empuje algunos objetos.

El siguiente remolino que saldrá en el código mas adelante se usa para que el circulo que cuelga se mueva a izquierda y derecha para poder empujar un objeto a la meta deseada. usando la ayuda de la gravedad.

El siguiente joint que nos presenta es el prismático, esto debido porque no se quiere que el carro anterior se caiga al vacío se crea un cubo que use este joint prismático para que vaya adelante y se detenga en un punto establecido en este caso 15. Para el prismático creamos dos objetos uno estático y otro dinámico ya que usara el estático como referencia donde tiene que quedar.

Ahora vienen las poleas, primero se le crea 4 objetos, 2 estáticos que funcionan como ancla, dos dinámicos para que se muevan, Para que no se vuelvan locas se crea dos objetos mas ambos dinámicos y prismáticos, ya que estos tienen la propiedad de que van a una dirección fija y no rotan. luego para añadirle un peso creamos un cubo con densidad de 1 para que pese.

Por ultimo usamos un while que crea la ventana y usa el tiempo del mundo para actualizar cada segundo.
En este caso ponemos todos los objetos creados con un update para que actualice sus movimientos, luego que limpie lo anterior, por ultimo hacemos que los objetos se dibujen en la pantalla para luego mostrarlo en la ventana, y se reinicia el while. 

Este código lo que hace en general es un carrito al caer encima de un triangulo o pendiente por la gravedad cae lentamente empujando dos circulos, estos circulos caen y el carrito retrocede y los circulos gracias a ser empujados por un remolino caen en una polea y hace que baje y el otro extremo de la polea sube con un cuadrado y gracias a un circulo que cuelga como péndulo arriba el cuadrado es empujado hacia una plataforma con un circulo para finalmente tirar el circulo.

Código:
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