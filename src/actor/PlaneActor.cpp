//
// Created by tony on 5/25/20.
//

#include "actor/PlaneActor.h"
#include "Game.h"
#include "graphics/Renderer.h"
#include "component/MeshComponent.h"

PlaneActor::PlaneActor(Game* game)
        :Actor(game)
{
    setScale(10.0f);
    auto* mc = new MeshComponent(this);
    mc->setMesh(getGame()->getRenderer()->getMesh("Assets/Plane.gpmesh"));
}