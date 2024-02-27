#ifndef __BSP_EPITTIMER_H
#define __BSP_EPITTIMER_H

void epit1_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(void);

#endif
