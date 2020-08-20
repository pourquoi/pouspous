import makeCrudModule from './crud';
import settingService from '@/services/setting';

export default makeCrudModule({service: settingService})