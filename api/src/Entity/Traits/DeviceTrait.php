<?php

namespace App\Entity\Traits;

use App\Entity\Device;
use Doctrine\ORM\Mapping as ORM;
use Symfony\Component\Serializer\Annotation\Groups;

trait DeviceTrait
{
    /**
     * @ORM\ManyToOne(targetEntity="Device", cascade="persist")
     * @ORM\JoinColumn(nullable=false)
     * @Groups({"read"})
     */
    protected $device;

    public function getDevice(): Device
    {
        return $this->device;
    }

    public function setDevice(Device $device): void
    {
        $this->device = $device;
    }
}