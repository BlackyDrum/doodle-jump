#include "../include/Collision.h"

void Collision::checkCollision(Player& player, Platform& platform, float velocity)
{
    b2Fixture* platformFixture = platform.getBody()->GetFixtureList();

    // Check if collision occurred using b2CollidePolygons
    if (b2TestOverlap(player.getBody()->GetFixtureList()->GetAABB(0), platformFixture->GetAABB(0)))
    {
        b2PolygonShape* playerShape = dynamic_cast<b2PolygonShape*>(player.getBody()->GetFixtureList()->GetShape());
        b2PolygonShape* platformShape = dynamic_cast<b2PolygonShape*>(platformFixture->GetShape());

        // Perform collision check using b2CollidePolygons
        b2Transform playerTransform = player.getBody()->GetTransform();
        b2Transform platformTransform = platform.getBody()->GetTransform();
        b2Manifold manifold;
        b2CollidePolygons(&manifold, playerShape, playerTransform, platformShape, platformTransform);

        if (manifold.pointCount > 0) {
            player.jump(velocity);

        }
    }
}