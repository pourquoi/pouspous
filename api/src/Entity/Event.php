<?php

namespace App\Entity;

use ApiPlatform\Core\Annotation\ApiFilter;
use ApiPlatform\Core\Annotation\ApiResource;
use Doctrine\ORM\Mapping as ORM;
use Symfony\Component\Serializer\Annotation\Groups;
use App\Dto\EventInput;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Filter\SearchFilter;
use ApiPlatform\Core\Bridge\Doctrine\Orm\Filter\OrderFilter;

/**
 * @ApiResource(
 *     normalizationContext={"groups"={"read"}},
 *     denormalizationContext={"groups"={"write"}},
 *     collectionOperations={
 *         "create"={
 *             "method"="POST",
 *             "input"=EventInput::class
 *         },
 *         "get"={"method"="GET"}
 *     },
 * )
 *
 * @ApiFilter(SearchFilter::class, properties={"type.name": "exact"})
 * @ApiFilter(OrderFilter::class, properties={"id": "DESC"})
 *
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
     * @ORM\Column(type="json", nullable=true)
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

    public function getValue()
    {
        return $this->value;
    }

    public function setValue($value): self
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
