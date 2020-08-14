<?php

namespace App\Entity;

use ApiPlatform\Core\Annotation\ApiResource;
use App\Repository\SensorLogRepository;
use Doctrine\ORM\Mapping as ORM;
use Symfony\Component\Serializer\Annotation\Groups;

/**
 * @ApiResource(
 *     normalizationContext={"groups"={"read"}},
 *     denormalizationContext={"groups"={"write"}},
 *     itemOperations={
 *          "get"={},
 *          "patch"={
 *              "input_formats"={"json"={"application/merge-patch+json"}}
 *          }
 *      }
 * )
 * @ORM\Entity(repositoryClass="App\Repository\EventTypeRepository")
 */
class EventType
{
    use Traits\DeviceTrait;

    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     * @Groups({"read"})
     */
    protected $id;

    /**
     * @ORM\Column(type="string", length=50)
     * @Groups({"read", "write"})
     */
    protected $name;

    /**
     * @ORM\Column(nullable=true)
     * @Groups({"read", "write"})
     */
    protected $label;

    /**
     * @ORM\Column(nullable=true)
     * @Groups({"read", "write"})
     */
    protected $display;

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

    public function getLabel(): ?string
    {
        return $this->label;
    }

    public function setLabel(?string $label): self
    {
        $this->label = $label;
        return $this;
    }

    public function getDisplay(): ?string
    {
        return $this->display;
    }

    public function setDisplay(?string $display): self
    {
        $this->display = $display;
        return $this;
    }
}
