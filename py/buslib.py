import serial, struct, sys, time, json
import collections
from colorama import Fore, Back, Style

commands = json.load(open('../shared/data/serial_commands.json','r'))
for name,props in sorted(commands.items(), key=lambda x: x[1]['id']):
    vars()['COMMAND_' + name.upper()] = props['id']

config_variables = json.load(open('../shared/data/config_variables.json','r'))
for name,props in sorted(config_variables.items(), key=lambda x: x[1]['id']):
    vars()['config_' + name] = props

fault_reasons = json.load(open('../shared/data/fault_reasons.json','r'))
for name,props in sorted(fault_reasons.items(), key=lambda x: x[1]['id']):
    vars()['fault_' + name] = props

production_states = json.load(open('../shared/data/production_states.json','r'))
component_states = json.load(open('../shared/data/component_states.json','r'))

speed = 115200
#speed = 117647

motor_current_factor = 17.8 # 3480 Ohms
motor_current_factor = 15 # 3300 Ohms

def msg(destgrp, destid, command, data, quiet=False):
    buf = b'U'
    buf += ((destgrp << 3) | destid | 0xC0).to_bytes(1, 'little');
    buf += command.to_bytes(1, 'little')
    buf += len(data).to_bytes(1, 'little')
    if type(data) == str:
        buf += data.encode('ascii')
    else:
        buf += data
    if not quiet:
        print('TX', repr(buf))
    return buf

ser = serial.Serial('/dev/ttyUSB0', speed, timeout=0.2)

motor_speed = 0x120


def receive():
    buf = b''
    header = b''
    for i in range(0, 100):
        header = ser.read(1)
        if header[0:1] == b'U':
            break
        if i == 0:
            print("*********** Invalid sync byte: %r" % header, end=" ")
        print('%r' % header, end=" ")
        sys.stdout.flush()
        header = None

    if header is None:
        return None

    header = header + ser.read(3)

    sync = header[0:1]
    address = header[1:2]
    command = header[2:3]
    length = int.from_bytes(header[3:4], 'little')
    while length > (len(buf)):
        buf += ser.read()
    return header + buf

def colored(msg, color):
    return color + msg + Fore.RESET

def xlat_fault(r):
    name = [k for k,v in fault_reasons.items() if v['id'] == r.fault][0]
    if name != 'none':
        name = colored(name, Fore.RED)
    r = r._replace(fault=name)
    return r

def xlat_pstate(r):
    name = [k for k,v in production_states.items() if v['id'] == r.pstate][0]
    if name != 'idle':
        name = colored(name, Fore.YELLOW)
    r = r._replace(pstate=name)
    return r

def xlat_tea_pstate(r):
    name = [k for k,v in production_states.items() if v['id'] == r.tea_pstate][0]
    if name != 'idle':
        name = colored(name, Fore.YELLOW)
    r = r._replace(tea_pstate=name)
    return r

def xlat_cstate(r):
    name = [k for k,v in component_states.items() if v['id'] == r.cstate][0]
    if name != 'ready':
        name = colored(name, Fore.RED)
    r = r._replace(cstate=name)
    return r

def _fmt_dbg(msg, pfx, t, xlatcb=None):
    reply_id = msg[2:3][0]
    reply = [v for k,v in commands.items() if v['id'] == reply_id][0]
    fmt = "<" + reply["format"]
    buf = msg[4:]
    data = pfx
    r = t(*struct.unpack(fmt, buf))
    if xlatcb is not None:
        r = xlatcb(r)
    if 'fault' in r._fields:
        r = xlat_fault(r)
    if 'pstate' in r._fields:
        r = xlat_pstate(r)
    if 'tea_pstate' in r._fields:
        r = xlat_tea_pstate(r)
    if 'cstate' in r._fields:
        r = xlat_cstate(r)
    if 'on' in r._fields:
        if r.on == 1:
            r = r._replace(on=colored(str(r.on), Fore.RED))
    for field in r._fields:
        data += ' '+field + ':'+ str(r.__dict__[field])
    return data

def format(msg, payload_only=False):
    if (msg is None):
        return "[Error]"

    address = msg[1:2][0]
    if address == 0xC0:
        address = 'Z'
    else:
        address = hex(address)
    command_id = msg[2:3][0]
    if command_id == 2:
        command = 'R'
    elif command_id == 0x90:
        command = 'RDBG'
    else:
        command = hex(command_id)

    buf = msg[4:]

    length = int.from_bytes(msg[3:4], 'little')
    data = ''
    for b in buf:
        data += '%02x ' % b

    decoded = ''

    if command_id == commands['error']['id']:
        error_id = buf[0]
        decoded += 'ERROR: %d' % error_id
        errors = set(filter(lambda x: x[0].startswith('ERROR_'), globals().items()))
        for error in errors:
            if error[1] == error_id:
                decoded += ' ' + error[0]
                break

    if command_id == commands['reply_dbg_motor']['id']:
        decoded += _fmt_dbg(
            lambda r: r._replace(
                mcurr='%0.1f'%(r.mcurr/motor_current_factor),
                topcurr='%0.1f'%(r.topcurr/motor_current_factor),
                lastoc='%0.1f'%(r.lastoc/motor_current_factor),
                wantedcurr='%0.1f'%(r.wantedcurr/motor_current_factor),
                speed='%d%%'%(r.speed*100/0x120),
                up=int((r.up&0x20)!=0)
                )
            )

    if command_id == commands['reply_dbg_adc']['id']:
        decoded += 'ADC'
        # adc dbg
        decoded += ' AN0/M_CUR: %d' % buf[0]
        decoded += ' AN1/PRE_G: %d' % buf[1]
        decoded += ' AN5/TMP_G: %d' % buf[2]
        decoded += ' AN6/TMP_Z: %d' % buf[3]
        decoded += ' AN7/TMP_S: %d' % buf[4]
        decoded += ' AN8/PRE_Z: %d (=%0.2f)' % (buf[5], 3.0/224.0*(buf[5]-24))
        decoded += ' CBT: %d' % buf[6]
        decoded += ' CBT-NC: %d' % buf[7]
        decoded += ' HBT: %d' % buf[8]
        decoded += ' FM: %d' % (buf[9] + (buf[10]<<8))
        decoded += ' PORTB: %x' % buf[11]

    if command_id == commands['reply_dbg_production']['id']:

    if command_id == commands['reply_dbg_hotwater_boiler']['id']:

    if command_id == commands['reply_dbg_coffee_boiler']['id']:

    if command_id == commands['reply_dbg_gpio']['id']:

    if payload_only and len(decoded) > 0:
        return decoded

    return 'RX to=%s cmd=%s %s %s (%d bytes)' % (address, command, data, decoded, length)

def ping():
    ser.write(msg(1, 0, COMMAND_PING, b'PING'))
    print(format(receive()))

def set_int(config, value):
    id = config['id']
    struct_fmt = '<BH'
    ser.write(msg(1, 0, COMMAND_SET, struct.pack(struct_fmt, id, value)))

def cmd(cmd_id, data=None, quiet=False):
    if data is None:
        data = b'XX'
    ser.write(msg(1, 0, cmd_id, data, quiet=quiet))

def drive(direction, length):
    cmd(COMMAND_DBG_STOP)
    time.sleep(0.2)

    # go
    cmd(direction, struct.pack('<HH', length, motor_speed))

    was_on = False
    try:
        while 1:
            cmd(COMMAND_DBG_QUERY_MOTOR)
            rx_data = receive()
            print(format(rx_data))
            if was_on:
                if rx_data[14] == 0:
                    break
            else:
                if rx_data[14] == 1:
                    was_on = True
            time.sleep(0.05)

    except KeyboardInterrupt as e:
        print(e)

    print("Stop...")
    cmd(COMMAND_DBG_STOP)
