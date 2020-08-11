<?php

namespace App\Tests;

use ApiPlatform\Core\Bridge\Symfony\Bundle\Test\ApiTestCase;
use Hautelook\AliceBundle\PhpUnit\RefreshDatabaseTrait;
use App\Entity\Device;

class DeviceTest extends ApiTestCase
{
    use RefreshDatabaseTrait;

    public function testGetCollection(): void
    {
        $response = static::createClient()->request('GET', '/api/devices?name=pouspous');

        $this->assertResponseIsSuccessful();

        $this->assertJsonContains(['hydra:totalItems' => 1]);
    }

    public function testCreateDevice(): void
    {
        $response = static::createClient()->request('POST', '/api/devices', ['json' => [
            'name' => 'test'
        ]]);

        $this->assertResponseStatusCodeSame(201);

        $this->assertJsonContains(['name' => 'test']);
    }
}
