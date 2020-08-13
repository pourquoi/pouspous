<?php

namespace App\Entity;

use ApiPlatform\Core\Annotation\ApiFilter;
use ApiPlatform\Core\Annotation\ApiResource;
use App\Repository\DeviceSettingRepository;
use Doctrine\ORM\Mapping as ORM;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Filter\OrderFilter;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Filter\SearchFilter;
use Symfony\Component\Serializer\Annotation\Groups;

/**
 * @ApiResource(
 *     normalizationContext={"groups"={"setting:read"}},
 *     denormalizationContext={"groups"={"write"}}
 * )
 *
 * @ApiFilter(SearchFilter::class, properties={"name"})
 * @ApiFilter(SearchFilter::class, properties={"device.name"})
 *
 * @ORM\Entity(repositoryClass=DeviceSettingRepository::class)
 */
class DeviceSetting
{
    use Traits\DeviceTrait;

    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    protected $id;

    /**
     * @ORM\Column(type="string", length=255)
     * @Groups({"setting:read", "setting:write"})
     */
    protected $name;

    /**
     * @ORM\Column(type="json")
     * @Groups({"setting:read", "setting:write"})
     */
    protected $value;

    /**
     * @Groups({"setting:read"})
     */
    public function getDeviceName()
    {
       return $this->getDevice() ? $this->getDevice()->getName() : null;
    }

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getName(): ?string
    {
        return $this->name;
    }

    public function setName(string $name): self
    {
        $this->name = $name;

        return $this;
    }

    public function getValue()
    {
        return $this->value;
    }

    public function setValue($value): self
    {
        $this->value = $value;

        return $this;
    }
}
