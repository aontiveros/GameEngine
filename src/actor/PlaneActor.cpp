//
// Created by tony on 5/25/20.
//

#include "../../header/actor/PlaneActor.h"
#include "../../header/Game.h"
#include "../../header/graphics/Renderer.h"
#include "../../header/component/MeshComponent.h"

PlaneActor::PlaneActor(Game* game)
        :Actor(game)
{
    setScale(10.0f);
    MeshComponent* mc = new MeshComponent(this);
    mc->setMesh(getGame()->getRenderer()->getMesh("Assets/Plane.gpmesh"));
}