CREATE TABLE Company_user
(
    id          BIGINT      NOT NULL,
    id_company  BIGINT      NOT NULL,
    email       VARCHAR(50) NOT NULL,
    telephone   VARCHAR(12) NOT NULL,
    password    VARCHAR(25) NOT NULL,
    first_name  VARCHAR(30) NOT NULL,
    family_name VARCHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE Company
(
    id BIGINT NOT NULL,
    name VARCHAR(60) NOT NULL,
    PRIMARY KEY (id)
);

ALTER TABLE
    Company_user ADD CONSTRAINT fk_company_user_company FOREIGN KEY(id) REFERENCES Company(id);