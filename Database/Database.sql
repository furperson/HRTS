BEGIN;


CREATE TYPE user_role AS ENUM ('admin', 'user');
CREATE TYPE task_state AS ENUM ('IDLE', 'SUCCESS', 'IN_WORK', 'STOP_BY_USER', 'FAILED');


CREATE TABLE users (
    username VARCHAR(255) PRIMARY KEY,
    password_hash VARCHAR(255) NOT NULL,
    role user_role NOT NULL DEFAULT 'user'
);


CREATE TABLE scenarios (
    scenario_name VARCHAR(255) NOT NULL,
    owner_name VARCHAR(255) NOT NULL REFERENCES users(username) ON DELETE CASCADE,
    test_duration_ms INTEGER NOT NULL,
    stop_scenario_pin INTEGER NOT NULL,
    PinBusGroup json DEFAULT '{}'::json,
    fpga_firmware_name VARCHAR(255),
    pin_scan_enable json DEFAULT '{}'::json,
    PRIMARY KEY (scenario_name,owner_name)
);



CREATE TABLE tasks (
    task_name VARCHAR(255),
    owner_name VARCHAR(255) NOT NULL REFERENCES users(username) ON DELETE CASCADE,
    scenario_name VARCHAR(255) NOT NULL,
    state task_state NOT NULL DEFAULT 'IDLE',
    BitArtef json DEFAULT '{}'::json,
    processing_start_time bigint, 
    processing_end_time bigint, 
    PRIMARY KEY (task_name,owner_name),
    FOREIGN KEY (scenario_name, owner_name) 
        REFERENCES scenarios (scenario_name, owner_name) 
        ON DELETE RESTRICT
);

COMMIT;
