<?php

namespace App\Dto;

use Symfony\Component\Serializer\Annotation\Groups;

final class SettingInput
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
    public $name;

    /**
     * @var float
     * @Groups({"write"})
     */
    public $value;
}