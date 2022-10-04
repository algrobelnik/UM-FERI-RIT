CREATE TABLE company (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    name VARCHAR(255) NOT NULL,
    ddv VARCHAR(50) NOT NULL,
    tax_number VARCHAR(50) NOT NULL,
    registration_number VARCHAR(50) NOT NULL,
    tax_payer TINYINT(1) NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    PRIMARY KEY (uuid)
);

CREATE TABLE invoice (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    invoice_number VARCHAR(255) DEFAULT "00-00000-01" NOT NULL,
    cashier VARCHAR(255) NOT NULL,
    eor VARCHAR(50) NOT NULL,
    zoi VARCHAR(50) NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    issuer_id BINARY(16) NOT NULL,
    customer_id BINARY(16),
    PRIMARY KEY (uuid),
    FOREIGN KEY (issuer_id) REFERENCES company(uuid),
    FOREIGN KEY (customer_id) REFERENCES company(uuid)
);

CREATE TABLE ddv (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    ddv_type CHAR(1) NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    price_id BINARY(16) NOT NULL,
    PRIMARY KEY (uuid),
    FOREIGN KEY (price_id) REFERENCES price(uuid)
);

CREATE TABLE price (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    value DECIMAL NOT NULL,
    currency VARCHAR(10) NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    PRIMARY KEY (uuid)
);

CREATE TABLE item (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    name VARCHAR(255) NOT NULL,
    quantity DECIMAL NOT NULL,
    gs1 VARCHAR(13) NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    price_id BINARY(16) NOT NULL,
    ddv_id BINARY(16) NOT NULL,
    invoice_id BINARY(16) NOT NULL,
    PRIMARY KEY (uuid),
    FOREIGN KEY (price_id) REFERENCES price(uuid),
    FOREIGN KEY (invoice_id) REFERENCES invoice(uuid)
);

CREATE TABLE internal_item (
    uuid BINARY(16) DEFAULT UNHEX(REPLACE(UUID(),"-","")) NOT NULL,
    internal_id INT(3) DEFAULT 200 NOT NULL,
    department INT(4) DEFAULT 0 NOT NULL,
    created TIMESTAMP DEFAULT NOW() NOT NULL,
    updated TIMESTAMP DEFAULT NOW() NOT NULL,
    item_id BINARY(16) NOT NULL,
    PRIMARY KEY (uuid),
    FOREIGN KEY (item_id) REFERENCES item(uuid)
);
