<?php

namespace App\Tests;

use ApiPlatform\Core\Bridge\Symfony\Bundle\Test\ApiTestCase;
use Hautelook\AliceBundle\PhpUnit\RefreshDatabaseTrait;
use App\Entity\Device;

class EventTest extends ApiTestCase
{
    use RefreshDatabaseTrait;

    public function testCreateEvent(): void
    {
        $response = static::createClient()->request('POST', '/api/events', ['json' => [
            'type' => 'watering',
            'value' => 1,
            'device' => 'pouspous'
        ]]);

        $this->assertResponseStatusCodeSame(201);

        $this->assertJsonContains(['value' => 1]);
    }

    public function testGetEvents(): void
    {
        $response = static::createClient()->request('GET', '/api/events', ['headers' => ['X-Device' => 'pouspous']]);

        $this->assertResponseStatusCodeSame(200);

        $this->assertJsonContains(['hydra:totalItems' => 100]);
    }
}
