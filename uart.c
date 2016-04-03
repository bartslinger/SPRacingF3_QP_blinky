/*****************************************************************************
* Product: Simple Blinky example
* Last Updated for Version: 5.5.0
* Date of the Last Update:  2015-08-30
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* Web:   www.state-machine.com
* Email: info@state-machine.com
*****************************************************************************/
#include "qpc.h"
#include "application.h"
#include "uart.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

/*..........................................................................*/
typedef struct {     /* the Blinky active object */
    QActive super;   /* inherit QActive */

    //QTimeEvt timeEvt; /* private time event generator */
} Uart;

static Uart l_uart1; /* the Blinky active object */

QActive * const A0_Uart1 = &l_uart1.super;

/* hierarchical state machine ... */
static QState Uart_initial(Uart * const me, QEvt const * const e);
static QState Uart_standby(Uart * const me, QEvt const * const e);

/*..........................................................................*/
void Uart1_ctor(void) {
    Uart * const me = &l_uart1;
    QActive_ctor(&me->super, Q_STATE_CAST(&Uart_initial));
}

/* HSM definition ----------------------------------------------------------*/
QState Uart_initial(Uart * const me, QEvt const * const e) {
    (void)e; /* avoid compiler warning about unused parameter */
    return Q_TRAN(&Uart_standby);
}
/*..........................................................................*/
QState Uart_standby(Uart * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            BSP_ledOff(0U);
            status = Q_HANDLED();
            break;
        }
        default: {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status;
}
