<?php

namespace App\Dto;

use Symfony\Component\Serializer\Annotation\Groups;

final class EventInput
{
    /**
     * @var string
     * @Groups({"write"})
     */
    public $device;

    /**
     * @var string
     * @Groups({"write"})
     */
    public $type;

    /**
     * @var float
     * @Groups({"write"})
     */
    public $value;
}