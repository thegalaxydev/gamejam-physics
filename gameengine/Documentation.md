# Documentation - Physics For Games 2023


## ShapeType
```cpp
enum ShapeType :
public GameGraphics::ShapeType
```

An enumerator that is used to define different types of shapes, and calls the appropriate
functions in ShapeComponent's 'draw()'  in order to draw them correctly.

<table>
<tr> 
<td>CIRCLE_CONTAINER</td> 
<td> 

```cpp
enum ShapeType
    {
        CIRCLE,
        BOX,
        CIRCLE_CONTAINER
    };
```
This is the addition of a new shape type in the GameGraphics namespace. When this shapetype
is called, it tells the ShapeComponent all the information it needs in order to correctly
draw this new shape type.
</table>

## ShapeComponent
```cpp
class ShapeComponent :
public GameEngine::Component
```

### Methods
<table>
<tr>
<td>draw</td> 
<td>

```cpp
void GameGraphics::ShapeComponent::draw()
```
Calls appropriate functions based on the enumerator given to it.
These functions draw the shapes in their appropriate positions,
can give them different colors, and have the abilitiy to draw them to the correct
scale.
</td>
</tr>
</table>

## ColliderComponent
```cpp
class ColliderComponent :
public GameEngine::Component
```

### enum 
An enumerator that is used to define the different types of colliders that can be assigned 
/given to an entity.

<table>
<tr> 
<td>CONTAINER</td> 
<td> 

```cpp
enum ColliderType
    {
        CIRCLE,
        AABB,
        CONTAINER
    };
```
This is the addition of a new collider type in the GamePhysics namespace and ColliderComponent class.
When this ColliderType is called, it tells the switch statement in the checkCollision()
 function which case is true.
</table>

### Methods
<table>
<tr>
<td>checkCollision</td> 
<td>

```cpp
GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
```
A function that looks at a switch statement and calls the appropriate collision detection
functions based on which case is true.
</td>
</tr>
</table>

<table>
<tr>
<td>checkCollisionContainer</td> 
<td>

```cpp
virtual Collision* checkCollisionContainer(CContainerColliderComponent* other) = 0;
```
A pure virtual function that forces derived classes to override and define
this function for how they detect collision with a container.
</td>
</tr>
</table>

## CContainerColliderComponent
```cpp
class CContainerColliderComponent : 
public ColliderComponent
```
A component used to give an entity a CContainerCollider.

### Properties
<table>
<tr> 
<td>m_radius</td> 
<td> 
Private

```cpp
float m_radius;
```
The value given to determine a CContainerCollider's radius. This is used to help with
collision detection between a container and other collider types.
</td>
</tr>
</table>

### Methods
<table>
<tr> 
<td>checkCollisionCircle</td> 
<td> 
Public

```cpp
GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
```
Function that determines collision detection between a container collider and a
circle collider. This function looks at its own position, the 'other' position, and finds
the distance between them. It checks to see if distance is less than the container's 
radius - the 'other' radius. If that parameter is true, then it deems that a collision
has not occured.
</td>
</tr>
</table>

<table>
<tr> 
<td>checkCollisionAABB</td> 
<td> 
Public

```cpp
GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;
```
Function that determines collision detection between a container collider and an
AABB collider. This function looks at its own position, the AABB's position, and the direction of the center
of the AABB to the center of the container. It finds the distance between the closest point of the AABB
that may be touching the circumference. If the distance is less than the radius of the container, then a 
collision has not occurred.
</td>
</tr>
</table>

<table>
<tr> 
<td>checkCollisionContainer</td> 
<td> 
Public

```cpp
GamePhysics::Collision* checkCollisionContainer(CContainerColliderComponent* other) override;
```
Function that determines collision detection between a container collider and a
container collider. This function does nothing in the CContainerComponentCollider class.
Since the function is pure virtual, it needs to be defined, but since no collisions
between containers has been planned, the function just returns nullptr.
</td>
</tr>
</table>

<table>
<tr> 
<td>draw</td> 
<td> 
Public

```cpp
void draw() override;
```
Function that looks at the owner's position, color assigned to it, and calls RAYLIB's
function for drawing circle lines.
</td>
</tr>
</table>

<table>
<tr> 
<td>getRadius</td> 
<td> 
Public

```cpp
float getRadius()
```
Function that gets the owner's radius.
</td>
</tr>
</table>

<table>
<tr> 
<td>setRadius</td> 
<td> 
Public

```cpp
float setRadius()
```
Function that sets the owner's radius.
</td>
</tr>
</table>

## CircleColliderComponent
```cpp
class CircleColliderComponent :
ColliderComponent
```
### Methods
<table>
<tr> 
<td>checkCollisionContainer</td> 
<td> 
Public

```cpp
GamePhysics::Collision* checkCollisionContainer(CContainerColliderComponent* other) override;
```
Function that determines collision detection between the circle collider and a
container. When the owner of this collider detects a collision with a container,
it will call the container's 'checkCollisionCircle' function, and uses all the 
collision data from 'other'.
</td>
</tr>
</table>

## AABBColliderComponent
```cpp
class AABBColliderComponent :
ColliderComponent
```
### Methods
<table>
<tr> 
<td>checkCollisionContainer</td> 
<td> 
Public

```cpp
GamePhysics::Collision* checkCollisionContainer(CContainerColliderComponent* other) override;
```
Function that determines collision detection between the AABB collider and a
container. When the owner of this collider detects a collision with a container,
it will call the container's 'checkCollisionAABB' function, and uses all the 
collision data from 'other'.
</td>
</tr>
</table>