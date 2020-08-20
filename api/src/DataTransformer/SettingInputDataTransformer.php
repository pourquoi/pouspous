<?php

namespace App\DataTransformer;

use ApiPlatform\Core\DataTransformer\DataTransformerInterface;
use ApiPlatform\Core\Validator\ValidatorInterface;
use App\Entity\DeviceSetting;
use App\Entity\Event;
use App\Entity\Device;
use App\Entity\EventType;
use App\Repository\DeviceRepository;
use App\Repository\EventTypeRepository;

class SettingInputDataTransformer implements DataTransformerInterface
{
    private $deviceRepository;
    private $validator;

    public function __construct(ValidatorInterface $validator, DeviceRepository $deviceRepository)
    {
        $this->validator = $validator;
        $this->deviceRepository = $deviceRepository;
    }

    public function transform($data, string $to, array $context = [])
    {
        $this->validator->validate($data);

        $setting = new DeviceSetting();
        $setting->setValue($data->value);
        $setting->setName($data->name);

        $device = $this->deviceRepository->findOneByName($data->device);
        if( !$device ) {
            return $data;
        }

        $setting->setDevice($device);

        return $setting;
    }

    public function supportsTransformation($data, string $to, array $context = []): bool
    {
        // in the case of an input, the value given here is an array (the JSON decoded).
        // if it's an event we transformed the data already
        if ($data instanceof DeviceSetting) {
            return false;
        }

        return DeviceSetting::class === $to && null !== ($context['input']['class'] ?? null);
    }
}

