--
-- PostgreSQL database dump
--

-- Dumped from database version 10.5 (Ubuntu 10.5-0ubuntu0.18.04)
-- Dumped by pg_dump version 10.5

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: key_data_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.key_data_id_seq
    START WITH 100
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.key_data_id_seq OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: key_data; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.key_data (
    id integer DEFAULT nextval('public.key_data_id_seq'::regclass) NOT NULL,
    key_type text,
    key_room integer,
    current_holder integer,
    storage_location text
);


ALTER TABLE public.key_data OWNER TO postgres;

--
-- Name: leases; Type: TABLE; Schema: public; Owner: iksf
--

CREATE TABLE public.leases (
    id integer NOT NULL,
    key_id integer,
    start_ts timestamp without time zone,
    end_ts timestamp without time zone
);


ALTER TABLE public.leases OWNER TO iksf;

--
-- Name: leases_id_seq; Type: SEQUENCE; Schema: public; Owner: iksf
--

CREATE SEQUENCE public.leases_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.leases_id_seq OWNER TO iksf;

--
-- Name: leases_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: iksf
--

ALTER SEQUENCE public.leases_id_seq OWNED BY public.leases.id;


--
-- Name: permission_group_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.permission_group_id_seq
    START WITH 100
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.permission_group_id_seq OWNER TO postgres;

--
-- Name: permission_group_membership; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.permission_group_membership (
    permission_group integer,
    user_id integer,
    start_timestamp timestamp without time zone,
    end_timestamp timestamp without time zone
);


ALTER TABLE public.permission_group_membership OWNER TO postgres;

--
-- Name: permission_group_white; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.permission_group_white (
    id integer NOT NULL,
    key_id integer,
    room_id integer,
    group_id integer
);


ALTER TABLE public.permission_group_white OWNER TO postgres;

--
-- Name: permission_group_white_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.permission_group_white_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.permission_group_white_id_seq OWNER TO postgres;

--
-- Name: permission_group_white_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.permission_group_white_id_seq OWNED BY public.permission_group_white.id;


--
-- Name: permission_groups; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.permission_groups (
    id integer NOT NULL,
    name text
);


ALTER TABLE public.permission_groups OWNER TO postgres;

--
-- Name: permission_groups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.permission_groups_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.permission_groups_id_seq OWNER TO postgres;

--
-- Name: permission_groups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.permission_groups_id_seq OWNED BY public.permission_groups.id;


--
-- Name: rooms_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.rooms_id_seq
    START WITH 100
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.rooms_id_seq OWNER TO postgres;

--
-- Name: rooms; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.rooms (
    id integer DEFAULT nextval('public.rooms_id_seq'::regclass) NOT NULL,
    name text
);


ALTER TABLE public.rooms OWNER TO postgres;

--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    name text
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.users_id_seq
    START WITH 100
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.users_id_seq OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- Name: leases id; Type: DEFAULT; Schema: public; Owner: iksf
--

ALTER TABLE ONLY public.leases ALTER COLUMN id SET DEFAULT nextval('public.leases_id_seq'::regclass);


--
-- Name: permission_group_white id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_group_white ALTER COLUMN id SET DEFAULT nextval('public.permission_group_white_id_seq'::regclass);


--
-- Name: permission_groups id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_groups ALTER COLUMN id SET DEFAULT nextval('public.permission_groups_id_seq'::regclass);


--
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- Data for Name: key_data; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.key_data (id, key_type, key_room, current_holder, storage_location) FROM stdin;
118	df	100	100	sdf
122	dfg	100	100	dfgs
120	dsf	100	101	aaa
117	dsf	100	100	dsf
121	gfhh	100	100	hhh
119	dfgggggg	100	100	ggg
\.


--
-- Data for Name: leases; Type: TABLE DATA; Schema: public; Owner: iksf
--

COPY public.leases (id, key_id, start_ts, end_ts) FROM stdin;
\.


--
-- Data for Name: permission_group_membership; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.permission_group_membership (permission_group, user_id, start_timestamp, end_timestamp) FROM stdin;
\.


--
-- Data for Name: permission_group_white; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.permission_group_white (id, key_id, room_id, group_id) FROM stdin;
\.


--
-- Data for Name: permission_groups; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.permission_groups (id, name) FROM stdin;
\.


--
-- Data for Name: rooms; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.rooms (id, name) FROM stdin;
100	N533
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, name) FROM stdin;
100	Kieran McKenzie
101	Jordan Low
\.


--
-- Name: key_data_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.key_data_id_seq', 122, true);


--
-- Name: leases_id_seq; Type: SEQUENCE SET; Schema: public; Owner: iksf
--

SELECT pg_catalog.setval('public.leases_id_seq', 1, false);


--
-- Name: permission_group_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.permission_group_id_seq', 100, false);


--
-- Name: permission_group_white_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.permission_group_white_id_seq', 1, false);


--
-- Name: permission_groups_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.permission_groups_id_seq', 1, false);


--
-- Name: rooms_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.rooms_id_seq', 100, true);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 101, true);


--
-- Name: key_data key_data_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.key_data
    ADD CONSTRAINT key_data_pkey PRIMARY KEY (id);


--
-- Name: leases leases_pkey; Type: CONSTRAINT; Schema: public; Owner: iksf
--

ALTER TABLE ONLY public.leases
    ADD CONSTRAINT leases_pkey PRIMARY KEY (id);


--
-- Name: permission_group_white permission_group_white_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_group_white
    ADD CONSTRAINT permission_group_white_pkey PRIMARY KEY (id);


--
-- Name: permission_groups permission_groups_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_groups
    ADD CONSTRAINT permission_groups_pkey PRIMARY KEY (id);


--
-- Name: rooms rooms_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.rooms
    ADD CONSTRAINT rooms_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: key_data key_data_current_holder_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.key_data
    ADD CONSTRAINT key_data_current_holder_fkey FOREIGN KEY (current_holder) REFERENCES public.users(id);


--
-- Name: key_data key_data_key_room_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.key_data
    ADD CONSTRAINT key_data_key_room_fkey FOREIGN KEY (key_room) REFERENCES public.rooms(id);


--
-- Name: leases leases_key_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: iksf
--

ALTER TABLE ONLY public.leases
    ADD CONSTRAINT leases_key_id_fkey FOREIGN KEY (key_id) REFERENCES public.key_data(id);


--
-- Name: permission_group_white permission_group_white_group_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_group_white
    ADD CONSTRAINT permission_group_white_group_id_fkey FOREIGN KEY (group_id) REFERENCES public.permission_groups(id);


--
-- Name: permission_group_white permission_group_white_room_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.permission_group_white
    ADD CONSTRAINT permission_group_white_room_id_fkey FOREIGN KEY (room_id) REFERENCES public.rooms(id);


--
-- Name: SEQUENCE key_data_id_seq; Type: ACL; Schema: public; Owner: postgres
--

GRANT ALL ON SEQUENCE public.key_data_id_seq TO iksf;


--
-- Name: SEQUENCE permission_group_id_seq; Type: ACL; Schema: public; Owner: postgres
--

GRANT ALL ON SEQUENCE public.permission_group_id_seq TO iksf;


--
-- Name: TABLE permission_group_membership; Type: ACL; Schema: public; Owner: postgres
--

GRANT ALL ON TABLE public.permission_group_membership TO iksf;


--
-- Name: SEQUENCE rooms_id_seq; Type: ACL; Schema: public; Owner: postgres
--

GRANT ALL ON SEQUENCE public.rooms_id_seq TO iksf;


--
-- Name: TABLE rooms; Type: ACL; Schema: public; Owner: postgres
--

GRANT ALL ON TABLE public.rooms TO iksf;


--
-- PostgreSQL database dump complete
--

