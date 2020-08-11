<?php

namespace App\DataTransformer;

use ApiPlatform\Core\DataTransformer\DataTransformerInterface;
use ApiPlatform\Core\Validator\ValidatorInterface;
use App\Entity\Event;
use App\Entity\Device;
use App\Entity\EventType;
use App\Repository\DeviceRepository;
use App\Repository\EventTypeRepository;

class EventInputDataTransformer implements DataTransformerInterface
{
    private $deviceRepository;
    private $eventTypeRepository;
    private $validator;

    public function __construct(ValidatorInterface $validator, DeviceRepository $deviceRepository, EventTypeRepository $eventTypeRepository)
    {
        $this->validator = $validator;
        $this->deviceRepository = $deviceRepository;
        $this->eventTypeRepository = $eventTypeRepository;
    }

    public function transform($data, string $to, array $context = [])
    {
        $this->validator->validate($data);

        $event = new Event();
        $event->setValue($data->value);

        $device = $this->deviceRepository->findOneByName($data->device);
        if( !$device ) {
            $device = new Device();
            $device->setName($data->device);
        }

        $type = $this->eventTypeRepository->getByNameAndDevice($data->type, $data->device);
        if( !$type ) {
            $type = new EventType();
            $type->setName($data->type);
            $type->setDevice($device);
        }

        $event->setType($type);

        return $event;
    }

    public function supportsTransformation($data, string $to, array $context = []): bool
    {
        // in the case of an input, the value given here is an array (the JSON decoded).
        // if it's an event we transformed the data already
        if ($data instanceof Event) {
            return false;
        }

        return Event::class === $to && null !== ($context['input']['class'] ?? null);
    }
}

