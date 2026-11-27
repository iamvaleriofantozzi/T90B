*** Settings ***
Suite Setup       Setup
Suite Teardown    Teardown
Test Setup        Reset Emulation
Resource          ${RENODEKEYWORDS}

*** Variables ***
${PLAT}           ${CURDIR}/t90b.repl
${CANDIDATE_ELF}  ${CURDIR}/../build/t90b.elf

*** Test Cases ***
Candidate Boot Keeps Heater Output Disabled
    Execute Command    mach create "t90b"
    Execute Command    machine LoadPlatformDescription @${PLAT}
    Execute Command    sysbus LoadELF @${CANDIDATE_ELF}
    Execute Command    cpu VectorTableOffset 0x08005000
    Execute Command    emulation RunFor "0.05"
    ${ccdat1}=         Execute Command    sysbus ReadDoubleWord 0x40012C34
    Should Be Equal As Integers    ${ccdat1}    0
