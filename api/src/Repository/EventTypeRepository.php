<?php

namespace App\Repository;

use App\Entity\EventType;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Common\Persistence\ManagerRegistry;

/**
 * @method EventType|null find($id, $lockMode = null, $lockVersion = null)
 * @method EventType|null findOneBy(array $criteria, array $orderBy = null)
 * @method EventType[]    findAll()
 * @method EventType[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class EventTypeRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, EventType::class);
    }

    /**
     * @param string|null $name
     * @param string|null $device
     * @return EventType|null
     * @throws \Doctrine\ORM\NonUniqueResultException
     */
    public function getByNameAndDevice(?string $name, ?string $device)
    {
        return $this->createQueryBuilder('t')
            ->innerJoin('t.device', 'd')
            ->where('t.name = :name')
            ->andWhere('d.name = :device')
            ->setParameter('name', $name)
            ->setParameter('device', $device)
            ->getQuery()->getOneOrNullResult();
    }
}