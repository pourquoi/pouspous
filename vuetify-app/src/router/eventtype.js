export default {
  path: '/event_types',
  name: 'event_types',
  component: () => import('../components/eventtype/Layout'),
  redirect: { name: 'EventTypeList' },
  children: [
    {
      name: 'EventTypeList',
      path: '',
      component: () => import('../views/eventtype/List')
    },
    {
      name: 'EventTypeCreate',
      path: 'new',
      component: () => import('../views/eventtype/Create')
    },
    {
      name: 'EventTypeUpdate',
      path: ':id/edit',
      component: () => import('../views/eventtype/Update')
    },
    {
      name: 'EventTypeShow',
      path: ':id',
      component: () => import('../views/eventtype/Show')
    }
  ]
};
