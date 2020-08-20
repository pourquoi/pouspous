<?php

namespace App\Tests;

use ApiPlatform\Core\Bridge\Symfony\Bundle\Test\ApiTestCase;
use Hautelook\AliceBundle\PhpUnit\RefreshDatabaseTrait;
use App\Entity\Device;

class SettingTest extends ApiTestCase
{
    use RefreshDatabaseTrait;

    public function testCreateSetting(): void
    {
        $response = static::createClient()->request('POST', '/api/device_settings', ['json' => [
            'name' => 'setting_1',
            'value' => 1,
            'device' => 'pouspous'
        ], 'headers' => ['X-Device' => 'pouspous']]);

        $this->assertResponseStatusCodeSame(201);

        $this->assertJsonContains(['value' => 1]);
    }

}
