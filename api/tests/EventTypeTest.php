<?php

namespace App\Tests;

use ApiPlatform\Core\Bridge\Symfony\Bundle\Test\ApiTestCase;
use App\Entity\EventType;
use Hautelook\AliceBundle\PhpUnit\RefreshDatabaseTrait;

class EventTypeTest extends ApiTestCase
{
    use RefreshDatabaseTrait;

    /**
     * @var \Doctrine\ORM\EntityManager
     */
    private $entityManager;

    protected function setUp(): void
    {
        $kernel = self::bootKernel();

        $this->entityManager = $kernel->getContainer()
            ->get('doctrine')
            ->getManager();
    }

    public function testPatchType(): void
    {
        $types = $this->entityManager->getRepository(EventType::class)->findByDeviceName('pouspous');

        $response = static::createClient()->request('PATCH', '/api/event_types/' . $types[0]->getId(), ['json' => [
            'display' => 'on/off'
        ], 'headers' => ['Content-Type' => 'application/merge-patch+json']]);

        $this->assertResponseStatusCodeSame(200);

        $this->assertJsonContains(['display' => 'on/off']);
    }

    protected function tearDown(): void
    {
        parent::tearDown();

        // doing this is recommended to avoid memory leaks
        $this->entityManager->close();
        $this->entityManager = null;
    }
}
