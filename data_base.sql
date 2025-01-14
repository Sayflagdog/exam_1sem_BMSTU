CREATE DATABASE company_management;

\c company_management;

CREATE TABLE employees (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    position VARCHAR(255) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL
);

CREATE TABLE projects (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    budget DECIMAL(15, 2) NOT NULL
);

CREATE TABLE employee_projects (
    employee_id INT REFERENCES employees(id) ON DELETE CASCADE,
    project_id INT REFERENCES projects(id) ON DELETE CASCADE,
    role_in_project VARCHAR(255) NOT NULL,
    PRIMARY KEY (employee_id, project_id)
);

CREATE ROLE admin;
CREATE ROLE manager;
CREATE ROLE analyst;

CREATE USER admin_user WITH PASSWORD 'admin_password';
CREATE USER manager_user WITH PASSWORD 'manager_password';
CREATE USER analyst_user WITH PASSWORD 'analyst_password';

GRANT admin TO admin_user;
GRANT manager TO manager_user;
GRANT analyst TO analyst_user;

GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO admin;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO admin;

GRANT SELECT ON employees, projects TO manager;
GRANT INSERT, SELECT ON employee_projects TO manager;

GRANT SELECT ON projects, employee_projects TO analyst;

BEGIN;
UPDATE projects SET budget = budget + 10000 WHERE id = 1;
ROLLBACK;
COMMIT;

BEGIN;
INSERT INTO employee_projects (employee_id, project_id, role_in_project) 
VALUES (1, 1, 'Developer');
ROLLBACK;
COMMIT;

BEGIN;
DELETE FROM projects WHERE id = 1;
ROLLBACK;
COMMIT;

CREATE TABLE audit_log (
    id SERIAL PRIMARY KEY,
    action VARCHAR(255) NOT NULL,
    table_name VARCHAR(255) NOT NULL,
    user_name VARCHAR(255) NOT NULL,
    action_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO audit_log (action, table_name, user_name) 
VALUES ('INSERT', 'employee_projects', 'manager_user');

SET ROLE manager;
SELECT * FROM employees;
INSERT INTO employee_projects (employee_id, project_id, role_in_project) VALUES (2, 1, 'Tester');
SET ROLE admin;
DROP TABLE employees;
