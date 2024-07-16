-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 16, 2024 at 03:22 PM
-- Server version: 11.1.5-MariaDB
-- PHP Version: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `test_app`
--

-- --------------------------------------------------------

--
-- Table structure for table `daily_sell_report`
--

CREATE TABLE `daily_sell_report` (
  `id` int(5) NOT NULL,
  `stock_id` int(11) DEFAULT NULL,
  `item_name` varchar(500) DEFAULT NULL,
  `qty` decimal(10,0) DEFAULT NULL,
  `unit_price` decimal(10,0) DEFAULT NULL,
  `total_price` decimal(10,0) DEFAULT NULL,
  `sell_date` date DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `item`
--

CREATE TABLE `item` (
  `id` int(5) NOT NULL,
  `stock_id` int(11) DEFAULT NULL,
  `item_name` varchar(500) DEFAULT NULL,
  `qty` decimal(5,0) DEFAULT NULL,
  `unit_price` decimal(10,0) DEFAULT NULL,
  `total_price` decimal(10,0) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `item`
--

INSERT INTO `item` (`id`, `stock_id`, `item_name`, `qty`, `unit_price`, `total_price`) VALUES
(1, 1, 'apple-ber', '5', '770', '3850'),
(2, 2, 'dell', '1', '11000', '11000'),
(3, 3, 'monitor2', '7', '6500', '45500'),
(4, 5, 'pp', '120', '100', '12000'),
(5, 6, 'br', '100', '300', '30000');

--
-- Triggers `item`
--
DELIMITER $$
CREATE TRIGGER `item_before_insert_unitprice` BEFORE INSERT ON `item` FOR EACH ROW BEGIN
    SET NEW.total_price = NEW.qty * NEW.unit_price;
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `item_before_update_unitprice` BEFORE UPDATE ON `item` FOR EACH ROW BEGIN
    SET NEW.total_price = NEW.qty * NEW.unit_price;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `loading`
--

CREATE TABLE `loading` (
  `id` int(5) NOT NULL,
  `vehicle_id` int(5) DEFAULT NULL,
  `item_id` int(5) DEFAULT NULL,
  `item_name` varchar(200) DEFAULT NULL,
  `qty` decimal(10,0) DEFAULT NULL,
  `day_type` varchar(100) DEFAULT NULL,
  `unload_time` varchar(1000) DEFAULT NULL,
  `load_time` varchar(1000) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `loading`
--

INSERT INTO `loading` (`id`, `vehicle_id`, `item_id`, `item_name`, `qty`, `day_type`, `unload_time`, `load_time`) VALUES
(1, 1, 1, NULL, '5', 'morning', NULL, '2024-05-30 11:49:38'),
(2, 2, 3, NULL, '3', 'evening', '2024-05-30 11:54:12', '2024-05-30 11:49:57'),
(3, 1, 3, NULL, '2', 'morning', NULL, '2024-05-30 11:55:37');

-- --------------------------------------------------------

--
-- Table structure for table `purchasing_reports`
--

CREATE TABLE `purchasing_reports` (
  `id` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `sales`
--

CREATE TABLE `sales` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `sales_reports`
--

CREATE TABLE `sales_reports` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `stock`
--

CREATE TABLE `stock` (
  `id` int(5) NOT NULL,
  `item_name` varchar(500) NOT NULL,
  `supplier_name` varchar(100) NOT NULL,
  `qty` decimal(10,0) NOT NULL,
  `unit_price` decimal(10,0) NOT NULL,
  `purchase_date` date DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `stock`
--

INSERT INTO `stock` (`id`, `item_name`, `supplier_name`, `qty`, `unit_price`, `purchase_date`) VALUES
(1, 'apple-ber', 'hirosha', '10', '770', '2023-10-15'),
(2, 'dell', 'badara-computers', '1', '11000', '2023-01-20'),
(3, 'monitor2', 'vscom', '12', '6500', '2024-05-30'),
(5, 'pp', 'pp', '120', '100', '2024-05-31'),
(6, 'br', 'wad', '100', '300', '2024-05-30');

-- --------------------------------------------------------

--
-- Table structure for table `vehicles`
--

CREATE TABLE `vehicles` (
  `id` int(11) NOT NULL,
  `reg_no` varchar(20) NOT NULL,
  `type` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `vehicles`
--

INSERT INTO `vehicles` (`id`, `reg_no`, `type`) VALUES
(1, 'CAR-1088', 'CAR'),
(2, '301-4585', 'lorry');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `item`
--
ALTER TABLE `item`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `stock_id` (`stock_id`);

--
-- Indexes for table `loading`
--
ALTER TABLE `loading`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `purchasing_reports`
--
ALTER TABLE `purchasing_reports`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sales`
--
ALTER TABLE `sales`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sales_reports`
--
ALTER TABLE `sales_reports`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `stock`
--
ALTER TABLE `stock`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `vehicles`
--
ALTER TABLE `vehicles`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `item`
--
ALTER TABLE `item`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `loading`
--
ALTER TABLE `loading`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `purchasing_reports`
--
ALTER TABLE `purchasing_reports`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `sales`
--
ALTER TABLE `sales`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `sales_reports`
--
ALTER TABLE `sales_reports`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `stock`
--
ALTER TABLE `stock`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `vehicles`
--
ALTER TABLE `vehicles`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
