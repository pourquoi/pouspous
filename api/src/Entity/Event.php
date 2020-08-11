<?php

namespace App\Entity;

use ApiPlatform\Core\Annotation\ApiResource;
use Doctrine\ORM\Mapping as ORM;
use Symfony\Component\Serializer\Annotation\Groups;
use App\Dto\EventInput;

/**
 * @ApiResource(
 *     normalizationContext={"groups"={"read"}},
 *     denormalizationContext={"groups"={"write"}},
 *     collectionOperations={
 *         "create"={
 *             "method"="POST",
 *             "input"=EventInput::class
 *         }
 *     },
 * )
 * @ORM\Entity()
 */
class Event
{
    use Traits\TimestampTrait;

    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     * @Groups({"read"})
     */
    protected $id;

    /**
     * @ORM\Column(type="float", nullable=true)
     * @Groups({"read", "write"})
     */
    protected $value;

    /**
     * @ORM\ManyToOne(targetEntity="EventType", cascade={"persist"})
     * @ORM\JoinColumn(nullable=false)
     * @Groups({"read"})
     */
    protected $type;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getValue(): ?float
    {
        return $this->value;
    }

    public function setValue(?float $value): self
    {
        $this->value = $value;
        return $this;
    }

    public function getType(): EventType
    {
        return $this->type;
    }

    public function setType(EventType $type): self
    {
        $this->type = $type;
        return $this;
    }
}
